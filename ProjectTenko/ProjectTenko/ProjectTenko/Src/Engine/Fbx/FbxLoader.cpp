#include "FbxLoader.h"
#include "../Graphics/DirectGraphics.h"
#include <string.h>


FBXMeshData* FbxLoader::LoadFBXMesh(const char* pFileName_)
{
	FBXMeshData* fbx_mesh_data = new FBXMeshData();
	ZeroMemory(fbx_mesh_data, sizeof(fbx_mesh_data));

	strcpy_s(m_RootPath, pFileName_);
	UINT i;
	for (i = strlen(m_RootPath); 0 < i; i--)
	{
		if (m_RootPath[i] == '/') break;
	}
	m_RootPath[i] = '\0';

	// FBXのマネージャーとインポーターの生成
	FbxManager* pManager = FbxManager::Create();
	FbxScene* pScene = FbxScene::Create(pManager, "");

	// ファイルのインポート
	FbxImporter* pImpoter = FbxImporter::Create(pManager, "");
	pImpoter->Initialize(pFileName_);
	bool result = pImpoter->Import(pScene);
	SAFE_DESTROY(pImpoter);

	fbxsdk::FbxGeometryConverter converter(pManager);
	// マテリアルと1メッシュ毎に分ける
	//converter.SplitMeshesPerMaterial(pScene, true);
	// 全てを三角形にする
	converter.Triangulate(pScene, true);

	FbxSystemUnit system_unit = pScene->GetGlobalSettings().GetSystemUnit();
	if (system_unit.GetScaleFactor() != 1.0f)
	{
		// シーンの単位をcmに設定する
		FbxSystemUnit::cm.ConvertScene(pScene);
	}


	// メッシュ分のバッファを確保
	int meshNum = pScene->GetSrcObjectCount<FbxMesh>();
	MeshData* pMeshData = (MeshData*)malloc(meshNum * sizeof(MeshData));
	ZeroMemory(pMeshData, meshNum * sizeof(MeshData));

	// マテリアル分のバッファを確保
	int materialNum = meshNum;
	MaterialData* pMaterialData = (MaterialData*)malloc(materialNum * sizeof(MaterialData));
	ZeroMemory(pMaterialData, materialNum * sizeof(MaterialData));

	D3DXMatrixIdentity(&fbx_mesh_data->Model.world);
	fbx_mesh_data->Model.meshNum = meshNum;
	fbx_mesh_data->Model.pMesh = pMeshData;
	fbx_mesh_data->Model.materialNum = materialNum;
	fbx_mesh_data->Model.pMaterial = pMaterialData;
	fbx_mesh_data->Model.boneNum = 0;
	ZeroMemory(fbx_mesh_data->Model.bone, sizeof(fbx_mesh_data->Model.bone));

	//	モーション情報取得
	FbxArray<FbxString*> names;
	pScene->FillAnimStackNameArray(names);

	int StartFrame = 0;
	if (names != NULL) {
		//	モーションが存在するとき
		FbxTakeInfo* take = pScene->GetTakeInfo(names[0]->Buffer());
		FbxLongLong start = take->mLocalTimeSpan.GetStart().Get();
		FbxLongLong stop = take->mLocalTimeSpan.GetStop().Get();
		FbxLongLong fps60 = FbxTime::GetOneFrameValue(FbxTime::eFrames60);
		StartFrame = (int)(start / fps60);

		fbx_mesh_data->Model.pMotion = new std::map<std::string, Motion>();
		(*fbx_mesh_data->Model.pMotion)["default"].numFrame = (int)((stop - start) / fps60);
	}
	fbx_mesh_data->Model.startFrame = StartFrame;

	// メッシュ単位で展開していく
	for (int i = 0; i < meshNum; i++)
	{
		FbxMesh* pMesh = pScene->GetSrcObject<FbxMesh>(i);

		LoadMesh(&pMeshData[i], pMesh);
		LoadMaterial(&pMaterialData[i], pMesh);
		LoadBone(&fbx_mesh_data->Model, &pMeshData[i], pMesh);
		pMeshData[i].materialIndex = i;
	}


	SAFE_DESTROY(pScene);
	SAFE_DESTROY(pManager);


	Play(fbx_mesh_data, "default");

	return fbx_mesh_data;
}

void FbxLoader::ReleaseFbxMesh(FBXMeshData * pData_)
{
	if (pData_ == nullptr) return;

	ReleaseModel(&pData_->Model);
}

bool FbxLoader::LoadMesh(MeshData * pMeshData_, FbxMesh * pMesh_)
{
	LoadIndeces(pMeshData_, pMesh_);

	LoadPosition(pMeshData_, pMesh_);
	LoadUV(pMeshData_, pMesh_);
	LoadColor(pMeshData_, pMesh_);
	LoadNormal(pMeshData_, pMesh_);


	int vertexNum = pMesh_->GetPolygonVertexCount();
	UINT size = (UINT)(vertexNum * sizeof(MeshVertex));
	MeshVertex* pVertices;
	// バッファをロックしてデータを書き込む
	pMeshData_->pVertexBuffer->Lock(0, size, (void**)& pVertices, 0);

	pMeshData_->pVertices = (MeshVertex*)malloc(size);
	memcpy(pMeshData_->pVertices, pVertices, size);

	pMeshData_->pVertexBuffer->Unlock();

	return true;
}

void FbxLoader::LoadMaterial(MaterialData * pMaterialData_, FbxMesh * pMesh_)
{
	InitMaterial(pMaterialData_, 1);
	FbxLayerElementMaterial* pElementMaterial = pMesh_->GetElementMaterial();

	if (pElementMaterial)
	{
		// マテリアル解析
		int index = pElementMaterial->GetIndexArray().GetAt(0);

		FbxSurfaceMaterial* pMaterial = pMesh_->GetNode()->GetSrcObject<FbxSurfaceMaterial>(index);
		if (pMaterial)
		{
			{
				FbxProperty prop = pMaterial->FindProperty(FbxSurfaceMaterial::sAmbient);
				const auto& color = prop.Get<FbxDouble3>();
				pMaterialData_->material.Ambient.r = static_cast<float>(color[0] * 255.0);
				pMaterialData_->material.Ambient.g = static_cast<float>(color[1] * 255.0);
				pMaterialData_->material.Ambient.b = static_cast<float>(color[2] * 255.0);
			}

			{
				FbxProperty prop = pMaterial->FindProperty(FbxSurfaceMaterial::sEmissive);
				const auto& color = prop.Get<FbxDouble3>();
				pMaterialData_->material.Emissive.r = static_cast<float>(color[0] * 255.0);
				pMaterialData_->material.Emissive.g = static_cast<float>(color[1] * 255.0);
				pMaterialData_->material.Emissive.b = static_cast<float>(color[2] * 255.0);
			}

			{
				FbxProperty prop = pMaterial->FindProperty(FbxSurfaceMaterial::sSpecular);
				const auto& color = prop.Get<FbxDouble3>();
				pMaterialData_->material.Specular.r = static_cast<float>(color[0] * 255.0);
				pMaterialData_->material.Specular.g = static_cast<float>(color[1] * 255.0);
				pMaterialData_->material.Specular.b = static_cast<float>(color[2] * 255.0);
			}
			FbxProperty prop = pMaterial->FindProperty(FbxSurfaceMaterial::sDiffuse);
			const auto& color = prop.Get<FbxDouble3>();
			pMaterialData_->material.Diffuse.r = static_cast<float>(color[0] * 255.0);
			pMaterialData_->material.Diffuse.g = static_cast<float>(color[1] * 255.0);
			pMaterialData_->material.Diffuse.b = static_cast<float>(color[2] * 255.0);


			//	テクスチャ読み込み
			const char* filename = NULL;
			int fileTextureCount = prop.GetSrcObjectCount<FbxFileTexture>();
			if (fileTextureCount > 0) {
				FbxFileTexture* FileTex = prop.GetSrcObject<FbxFileTexture>(0);
				filename = FileTex->GetFileName();
			}
			else {
				int numLayer = prop.GetSrcObjectCount<FbxLayeredTexture>();
				if (numLayer > 0) {
					FbxLayeredTexture* LayerTex = prop.GetSrcObject<FbxLayeredTexture>(0);
					FbxFileTexture* FileTex = LayerTex->GetSrcObject<FbxFileTexture>(0);
					filename = FileTex->GetFileName();
				}
			}
			if (filename == NULL) return;

			//	テクスチャーの取得
			char* pFileName;
			size_t size = 0;
			FbxUTF8ToAnsi(filename, pFileName, &size);

			// PSDが使用されている場合は読めないのでTGAで試す
			char* ext = (char*)strstr(pFileName, ".psd");
			if (ext)
			{
				strcpy_s(ext, 5, ".tga");
			}

			char path[MAX_PATH];
			if (strstr(pFileName, "\\"))
			{
				strcpy_s(path, pFileName);
			}
			else
			{
				strcpy_s(path, m_RootPath);
				strcat_s(path, "/texture/");
				strcat_s(path, pFileName);
			}
			
			LoadTexture(path, &pMaterialData_->textureData);

			FbxFree(pFileName);
		}
	}
}

void FbxLoader::LoadBone(Model * pModel_, MeshData * pMeshData_, FbxMesh * pMesh_)
{
	// スキン情報の有無
	int skinCount = pMesh_->GetDeformerCount(FbxDeformer::eSkin);
	if (skinCount <= 0)
	{
		return;
	}
	int vertexNum = pMeshData_->vertexNum;
	UINT size = (UINT)(vertexNum * sizeof(MeshVertex));

	MeshVertex* pVertices;
	// バッファをロックしてデータを書き込む
	pMeshData_->pVertexBuffer->Lock(0, size, (void**)& pVertices, 0);

	FbxSkin* pSkin = (FbxSkin*)pMesh_->GetDeformer(0, FbxDeformer::eSkin);
	// ボーン数
	int nBone = pSkin->GetClusterCount();
	//	全ボーン情報取得
	for (int bone = 0; bone < nBone; bone++)
	{
		//	ボーン情報取得
		FbxCluster* pCluster = pSkin->GetCluster(bone);
		FbxAMatrix trans;
		pCluster->GetTransformMatrix(trans);
		trans.mData[0][1] *= -1;
		trans.mData[0][2] *= -1;
		trans.mData[1][0] *= -1;
		trans.mData[2][0] *= -1;
		trans.mData[3][0] *= -1;

		//	ボーン名取得
		const char* pName = pCluster->GetLink()->GetName();

		Bone* pBone;
		//	ボーン検索
		int bone_no = FindBone(pModel_, pName);
		if (bone_no != -1)
		{
			pBone = &pModel_->bone[bone_no];
		}
		else
		{
			bone_no = pModel_->boneNum;
			pBone = &pModel_->bone[bone_no];
			pModel_->boneNum++;

			strcpy_s(pBone->name, pName);
			//	オフセット行列作成
			FbxAMatrix LinkMatrix;
			pCluster->GetTransformLinkMatrix(LinkMatrix);
			LinkMatrix.mData[0][1] *= -1;
			LinkMatrix.mData[0][2] *= -1;
			LinkMatrix.mData[1][0] *= -1;
			LinkMatrix.mData[2][0] *= -1;
			LinkMatrix.mData[3][0] *= -1;

			FbxAMatrix Offset = LinkMatrix.Inverse() * trans;
			FbxDouble* OffsetM = (FbxDouble*)Offset;

			//	オフセット行列保存
			for (int i = 0; i < 16; i++)
			{
				pBone->offset.m[i / 4][i % 4] = (float)OffsetM[i];
			}
			//	キーフレーム読み込み
			LoadKeyFrames(pModel_, "default", bone_no, pCluster->GetLink());
		}

		//	ウェイト読み込み
		int weightCount = pCluster->GetControlPointIndicesCount();
		int* pWeightIndex = pCluster->GetControlPointIndices();
		double* wgt = pCluster->GetControlPointWeights();

		int* index = pMesh_->GetPolygonVertices();


		for (int i = 0; i < weightCount; i++)
		{
			int wgtIdx2 = pWeightIndex[i];
			//	全ポリゴンからwgtIdx2番目の頂点検索
			for (int vtxIdx = 0; vtxIdx < vertexNum; vtxIdx++)
			{
				if (index[vtxIdx] != wgtIdx2) continue;
				//	頂点にウェイト保存
				int weightCount;
				for (weightCount = 0; weightCount < 4; weightCount++)
				{
					if (pVertices[vtxIdx].weight[weightCount] <= 0.0f)
					{
						break;
					}
				}
				if (4 <= weightCount) continue;

				pVertices[vtxIdx].index[weightCount] = bone_no;
				pVertices[vtxIdx].weight[weightCount] = (float)wgt[i];
			}
		}
	}
	//	ウェイト正規化
	// ５本以上にまたっがてる場合のため
	for (int vtxIdx = 0; vtxIdx < vertexNum; vtxIdx++)
	{
		float n = 0;
		int weightCount;
		//	頂点のウェイトの合計値
		for (weightCount = 0; weightCount < 4; weightCount++)
		{
			if (pVertices[vtxIdx].weight[weightCount] <= 0.0f)
			{
				break;
			}
			n += pVertices[vtxIdx].weight[weightCount];
		}
		//	正規化
		for (weightCount = 0; weightCount < 4; weightCount++)
		{
			pVertices[vtxIdx].weight[weightCount] /= n;
		}
	}
	pMeshData_->pVertexBuffer->Unlock();
}

int FbxLoader::FindBone(Model * pModel_, const char* pName_)
{
	for (UINT boneIdx = 0; boneIdx < pModel_->boneNum; boneIdx++)
	{
		if (strcmp(pModel_->bone[boneIdx].name, pName_) == 0)
		{
			return (int)boneIdx;
		}
	}
	return -1;
}

void FbxLoader::LoadKeyFrames(Model * pModel_, std::string name_, int bone_, FbxNode * pBoneNode_)
{
	//	メモリ確保
	Motion* pMotion = &(*pModel_->pMotion)[name_];
	pMotion->pKey[bone_] = (D3DXMATRIX*)malloc(sizeof(D3DXMATRIX) * (pMotion->numFrame + 1));

	double time = (double)pModel_->startFrame * (1.0 / 60);
	FbxTime T;
	for (UINT f = 0; f < pMotion->numFrame; f++)
	{
		T.SetSecondDouble(time);
		//	T秒の姿勢行列をGet
		FbxMatrix m = pBoneNode_->EvaluateGlobalTransform(T);
		m.mData[0][1] *= -1;// _12
		m.mData[0][2] *= -1;// _13
		m.mData[1][0] *= -1;// _21
		m.mData[2][0] *= -1;// _31
		m.mData[3][0] *= -1;// _41

		FbxDouble* mat = (FbxDouble*)m;
		for (int i = 0; i < 16; i++)
		{
			pMotion->pKey[bone_][f].m[i / 4][i % 4] = (float)mat[i];
		}

		time += 1.0 / 60.0;
	}
}

void FbxLoader::Play(FBXMeshData * pData_, std::string name_)
{
	if (pData_ == nullptr) return;
	strcpy_s(pData_->motion, name_.c_str());
	pData_->frame = 0.0f;
}

void FbxLoader::LoadIndeces(MeshData * pMeshData_, FbxMesh * pMesh_)
{
	int polyCount = pMesh_->GetPolygonCount();
	UINT size = (UINT)((polyCount * 3) * sizeof(UINT16));

	pMeshData_->fvf = FVF_MESH_TEX_VERTEX;
	pMeshData_->primType = D3DPT_TRIANGLELIST;
	pMeshData_->primNum = (UINT)polyCount;
	pMeshData_->indexNum = (UINT)(polyCount * 3);
	pMeshData_->pIndexBuffer = CreateIndexBuffer(NULL, size);

	UINT16* pIndeces;
	// バッファをロックしてデータを書き込む
	pMeshData_->pIndexBuffer->Lock(0, size, (void**)& pIndeces, 0);

	for (int polyIdx = 0; polyIdx < polyCount; polyIdx++)
	{
		pIndeces[polyIdx * 3 + 0] = polyIdx * 3 + 2;
		pIndeces[polyIdx * 3 + 1] = polyIdx * 3 + 1;
		pIndeces[polyIdx * 3 + 2] = polyIdx * 3 + 0;
	}
	pMeshData_->pIndexBuffer->Unlock();
}

void FbxLoader::LoadPosition(MeshData * pMeshData_, FbxMesh * pMesh_)
{
	int vertexNum = pMesh_->GetPolygonVertexCount();
	UINT size = (UINT)(vertexNum * sizeof(MeshVertex));

	FbxVector4* source = pMesh_->GetControlPoints();
	// メッシュのトランスフォーム
	FbxVector4 T = pMesh_->GetNode()->GetGeometricTranslation(FbxNode::eSourcePivot);
	FbxVector4 R = pMesh_->GetNode()->GetGeometricRotation(FbxNode::eSourcePivot);
	FbxVector4 S = pMesh_->GetNode()->GetGeometricScaling(FbxNode::eSourcePivot);
	FbxAMatrix TRS = FbxAMatrix(T, R, S);
	//	全頂点変換
	for (int v = 0; v < pMesh_->GetControlPointsCount(); v++)
	{
		source[v] = TRS.MultT(source[v]);
	}

	pMeshData_->vertexNum = (UINT)vertexNum;
	pMeshData_->vertexStride = sizeof(MeshVertex);
	pMeshData_->pVertexBuffer = CreateVertexBuffer(NULL, size);

	MeshVertex* pVertices;
	// バッファをロックしてデータを書き込む
	pMeshData_->pVertexBuffer->Lock(0, size, (void**)& pVertices, 0);

	int* pIndex = pMesh_->GetPolygonVertices();
	for (int vtxIdx = 0; vtxIdx < vertexNum; vtxIdx++)
	{
		int index = pIndex[vtxIdx];
		FbxVector4& pos = source[index];

		pVertices[vtxIdx].x = -(float)pos[0];
		pVertices[vtxIdx].y = (float)pos[1];
		pVertices[vtxIdx].z = (float)pos[2];
		pVertices[vtxIdx].nx = 0.0f;
		pVertices[vtxIdx].ny = 1.0f;
		pVertices[vtxIdx].nz = 0.0f;
		pVertices[vtxIdx].u = 0.0f;
		pVertices[vtxIdx].v = 0.0f;
		pVertices[vtxIdx].color = 0xffffff;
		ZeroMemory(pVertices[vtxIdx].index, sizeof(pVertices[vtxIdx].index));
		ZeroMemory(pVertices[vtxIdx].weight, sizeof(pVertices[vtxIdx].weight));
	}
	pMeshData_->pVertexBuffer->Unlock();
}

void FbxLoader::LoadUV(MeshData * pMeshData_, FbxMesh * pMesh_)
{
	FbxStringList uvSetNames;
	pMesh_->GetUVSetNames(uvSetNames);

	FbxArray<FbxVector2> uvSets;
	pMesh_->GetPolygonVertexUVs(uvSetNames.GetStringAt(0), uvSets);

	UINT size = pMeshData_->vertexNum * sizeof(MeshVertex);

	MeshVertex* pVertices;
	// バッファをロックしてデータを書き込む
	pMeshData_->pVertexBuffer->Lock(0, size, (void**)& pVertices, 0);

	for (int vtxIdx = 0; vtxIdx < uvSets.Size(); vtxIdx++)
	{
		FbxVector2& uvSet = uvSets[vtxIdx];

		pVertices[vtxIdx].u = (float)uvSet[0];
		pVertices[vtxIdx].v = (float)(1.0 - uvSet[1]);
	}
	pMeshData_->pVertexBuffer->Unlock();
}

void FbxLoader::LoadColor(MeshData * pMeshData_, FbxMesh * pMesh_)
{
	int colorElementCount = pMesh_->GetElementVertexColorCount();
	if (colorElementCount == 0) return;

	FbxLayerElementVertexColor * pColor = pMesh_->GetElementVertexColor(0);

	FbxLayerElement::EMappingMode mapMode = pColor->GetMappingMode();
	FbxLayerElement::EReferenceMode refMode = pColor->GetReferenceMode();

	if (mapMode == FbxLayerElement::eByPolygonVertex)
	{
		if (refMode == FbxLayerElement::eIndexToDirect)
		{
			UINT size = pMeshData_->vertexNum * sizeof(MeshVertex);
			MeshVertex* pVertices;
			// バッファをロックしてデータを書き込む
			pMeshData_->pVertexBuffer->Lock(0, size, (void**)& pVertices, 0);

			FbxLayerElementArrayTemplate<FbxColor>& colors = pColor->GetDirectArray();
			FbxLayerElementArrayTemplate<int>& indeces = pColor->GetIndexArray();
			for (int i = 0; i < indeces.GetCount(); i++)
			{
				const FbxColor& color = colors.GetAt(indeces.GetAt(i));
				DWORD a = (DWORD)(color.mAlpha * 255.0);
				DWORD r = (DWORD)(color.mRed * 255.0);
				DWORD g = (DWORD)(color.mGreen * 255.0);
				DWORD b = (DWORD)(color.mBlue * 255.0);

				pVertices[i].color = (a << 24) + (r << 16) + (g << 8) + (b);
			}
			pMeshData_->pVertexBuffer->Unlock();
		}
	}
}

void FbxLoader::LoadNormal(MeshData * pMeshData_, FbxMesh * pMesh_)
{
	FbxArray<FbxVector4> normals;
	pMesh_->GetPolygonVertexNormals(normals);

	UINT size = pMeshData_->vertexNum * sizeof(MeshVertex);

	MeshVertex* pVertices;
	// バッファをロックしてデータを書き込む
	pMeshData_->pVertexBuffer->Lock(0, size, (void**)& pVertices, 0);

	for (int vtxIdx = 0; vtxIdx < normals.Size(); vtxIdx++)
	{
		FbxVector4& normal = normals[vtxIdx];

		pVertices[vtxIdx].nx = -(float)normal[0];
		pVertices[vtxIdx].ny = (float)normal[1];
		pVertices[vtxIdx].nz = (float)normal[2];
	}
	pMeshData_->pVertexBuffer->Unlock();
}
