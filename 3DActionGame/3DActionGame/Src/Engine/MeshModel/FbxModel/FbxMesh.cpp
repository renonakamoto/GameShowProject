#include <codecvt>
#include "../../../DirectXTex/DirectXTex.h"
#include "FbxMesh.h"
#include "../../../Utility/Utility.h"


#if _DEBUG
#pragma comment(lib, "Src/DirectXTex/x64/Debug/DirectXTex.lib")
#else
#pragma comment(lib, "Src/DirectXTex/x64/Release/DirectXTex.lib")
#endif


bool FbxModel::Load(const char* fileName_, ID3D11Device* device_, VertexShader* vertexShader_)
{
#pragma region Fbxオブジェクトの作成

	// SDKを管理しているマネージャークラスの生成
	FbxManager* manager = FbxManager::Create();
	if (manager == nullptr) {
		// マネージャーの作成失敗
		return false;
	}

	// 入出力設定の作成と設定
	FbxIOSettings* ios = FbxIOSettings::Create(manager, IOSROOT);
	manager->SetIOSettings(ios);

	// fbxファイルの読み込み、解析をしてくれるインポーターの生成
	FbxImporter* importer = FbxImporter::Create(manager, "");
	if (importer == nullptr) {
		// Importerの作成失敗
		manager->Destroy();
		return false;
	}

	// FbxSceneの作成
	// Importerによって分解されたfbxのデータを保存するためのクラス
	FbxScene* fbx_scene = FbxScene::Create(manager, "");
	if (fbx_scene == nullptr) {
		// Sceneの作成失敗
		manager->Destroy();
		return false;
	}

	// FBXファイルを開いて、初期化する
	if (importer->Initialize(fileName_) == false)
	{
		// 読み込み失敗
		manager->Destroy();

		return false;
	}

	// ImporterでFbxデータを分解してSceneにインポートする
	if (importer->Import(fbx_scene) == false) {
		// インポート失敗
		manager->Destroy();

		return false;
	}
	// インポートが完了したらインポーターは不要なので破棄する
	importer->Destroy();

	// ジオメトリコンバーターを作成
	FbxGeometryConverter geometry_converter(manager);
	// メッシュに使われているマテリアル単位でメッシュを分割する
	geometry_converter.SplitMeshesPerMaterial(fbx_scene, true);

	// センチメートル単位にコンバートする
	FbxSystemUnit scene_system_unit = fbx_scene->GetGlobalSettings().GetSystemUnit();
	if (scene_system_unit.GetScaleFactor() != 1.0f)
	{
		FbxSystemUnit::cm.ConvertScene(fbx_scene);
	}
	// ポリゴンが三角形よりも多いと困るので三角形に変換する
	geometry_converter.Triangulate(fbx_scene, true);

#pragma endregion

	
	// マテリアルの数を取得
	int material_num = fbx_scene->GetSrcObjectCount<FbxSurfaceMaterial>();
	// マテリアルの読み込み
	for (int i = 0; i < material_num; ++i)
	{
		FbxSurfaceMaterial* material = fbx_scene->GetSrcObject<FbxSurfaceMaterial>(i);
		LoadMaterial(material);
	}

	// メッシュの数を取得
	int mesh_count = fbx_scene->GetSrcObjectCount<FbxMesh>();
	// メッシュの読み込み
	for (int i = 0; i < mesh_count; ++i)
	{
		FbxMesh* mesh = fbx_scene->GetSrcObject<FbxMesh>(i);

		// メッシュの情報を保存する変数
		MeshData mesh_data;

		// 頂点座標の取得
		LoadVertices(mesh_data, mesh);
		// 法線ベクトルの取得
		LoadNormals(mesh_data, mesh);
		// 頂点番号の取得
		LoadIndices(mesh_data, mesh);
		// テクスチャ座標の取得
		LoadUV(mesh_data, mesh);
		// 頂点カラーの取得
		LoadVertexColors(mesh_data, mesh);
		// マテリアル名の取得
		LoadMaterialNames(mesh_data, mesh);
		// ボーンの取得
		LoadBones(mesh_data, mesh);

		// メッシュデータを追加
		m_MeshList.emplace_back(mesh_data);
	}

	// マネージャーの破棄
	if (manager != nullptr)
	{
		// マネージャーのDestroyを呼べばその他のFBXオブジェクトも破棄される
		manager->Destroy();
	}

	// バーテックスバッファの作成
	if (CreateVertexBuffer(device_) == false)
	{
		return false;
	}

	// インデックスバッファの作成
	if (CreateIndexBuffer(device_) == false)
	{
		return false;
	}

	// 入力レイアウトの作成
	if (CreateInputLayout(device_, vertexShader_) == false)
	{
		return false;
	}


	// 読み込み成功
	return true;
}

bool FbxModel::LoadMotion(std::string keyword_, const char* fileName_)
{
	// SDKを管理しているマネージャークラスの生成
	FbxManager* manager = FbxManager::Create();
	if (manager == nullptr) {
		// マネージャーの作成失敗
		return false;
	}

	FbxIOSettings* ios = FbxIOSettings::Create(manager, IOSROOT);
	manager->SetIOSettings(ios);

	// fbxファイルの読み込み、解析をしてくれるクラスの生成
	// 第一 : マネージャー
	// 第二 : オブジェクトにつける名前(空でも可)
	FbxImporter* importer = FbxImporter::Create(manager, "");
	if (importer == nullptr) {
		// Importerの作成失敗
		manager->Destroy();
		return false;
	}

	// FbxSceneの作成
	// Importerによって分解されたfbxのデータを保存するためのクラス
	FbxScene* fbx_scene = FbxScene::Create(manager, "");
	if (fbx_scene == nullptr) {
		// Sceneの作成失敗
		manager->Destroy();
		return false;
	}

	// FBXファイルを開いて、初期化する
	if (importer->Initialize(fileName_) == false) {
		// 読み込み失敗
		manager->Destroy();

		return false;
	}

	// ImporterでFbxデータを分解してSceneにインポートする
	if (importer->Import(fbx_scene) == false) {
		// インポート失敗
		manager->Destroy();
		importer->Destroy();
		fbx_scene->Destroy();

		return false;
	}
	importer->Destroy();


	// モーション情報取得
	FbxArray<FbxString*> names;
	fbx_scene->FillAnimStackNameArray(names);

	// モーションが存在しないとき
	if (names == nullptr) return false;

	// モーション情報を取得
	FbxTakeInfo* take_info = fbx_scene->GetTakeInfo(names[0]->Buffer());

	// モーションの開始時間と終了時間を60Fpsで求める
	FbxLongLong start = take_info->mLocalTimeSpan.GetStart().Get();
	FbxLongLong stop = take_info->mLocalTimeSpan.GetStop().Get();
	FbxLongLong fps60 = FbxTime::GetOneFrameValue(FbxTime::eFrames60);
	m_StartFrame = static_cast<int>(start / fps60);
	m_Motion[keyword_].FrameNum = static_cast<UINT>((stop - start) / fps60);

	FbxNode* root = fbx_scene->GetRootNode();

	for (int b = 0; b < m_BoneNum; ++b)
	{
		// ボーンノードを検索
		FbxNode* bone = root->FindChild(m_Bone[b].Name);
		if (bone == nullptr)
		{
			continue;
		}

		// キーフレーム読み込み
		LoadKeyFrame(keyword_, b, bone);
	}

	fbx_scene->Destroy();
	manager->Destroy();

	return true;
}


void FbxModel::Render(DirectGraphics* graphics_, DirectX::XMFLOAT3 pos_, DirectX::XMFLOAT3 scale_, DirectX::XMFLOAT3 degree_)
{
	using namespace DirectX;

	UINT strides = sizeof(CVertex);
	UINT offsets = 0;
	ID3D11DeviceContext* context = graphics_->GetContext();
	context->IASetInputLayout(m_InputLayout);

	for (auto& mesh : m_MeshList)
	{
		context->IASetVertexBuffers(
			0,
			1,
			&mesh.m_VertexBuffer,
			&strides,
			&offsets);

		context->IASetIndexBuffer(
			mesh.m_IndexBuffer,
			DXGI_FORMAT_R32_UINT,
			0);

		// ワールド行列の作成
		DirectX::XMMATRIX mat_world, mat_trans, mat_rot_x, mat_rot_y, mat_rot_z, mat_scale;
		mat_trans = XMMatrixTranslation(pos_.x, pos_.y, pos_.z);
		mat_rot_x = XMMatrixRotationX(XMConvertToRadians(degree_.x));
		mat_rot_y = XMMatrixRotationY(XMConvertToRadians(degree_.y));
		mat_rot_z = XMMatrixRotationZ(XMConvertToRadians(degree_.z));
		mat_scale = XMMatrixScaling(scale_.x, scale_.y, scale_.z);
		mat_world = mat_scale * mat_rot_x * mat_rot_y * mat_rot_z * mat_trans;

		// ワールド行列をコンスタントバッファに設定
		XMStoreFloat4x4(&graphics_->GetConstantBufferData()->World, XMMatrixTranspose(mat_world));


		// コンスタントバッファにマテリアル情報を保存する
		//graphics_->SetMaterial(&m_Materials[mesh.m_MaterialName]);

		// ボーン行列
		Motion* motion = &m_Motion[m_PlayMotion];
		if (motion != nullptr)
		{
			if (motion->FrameNum >= 0)
			{
				float frame = m_Frame;
				int f = static_cast<int>(frame);

				for (UINT b = 0; b < m_BoneNum; ++b)
				{
					if (motion->Key[b].empty()) {
						//graphics_->GetConstantBufferData()->Bone[b] = DirectX::XMMatrixIdentity();
						continue;
					}

					m_Bone[b].Transform = motion->Key[b][f] * (1.0f - (frame - static_cast<int>(frame))) + motion->Key[b][(size_t)f + 1] * (frame - static_cast<int>(frame));
					DirectX::XMMATRIX mat = m_Bone[b].Offset * m_Bone[b].Transform;
					graphics_->GetConstantBufferData()->Bone[b] = DirectX::XMMatrixTranspose(mat);
				}
			}
		}


		// コンスタントバッファの更新
		graphics_->GetContext()->UpdateSubresource(graphics_->GetConstantBuffer(), 0, NULL, graphics_->GetConstantBufferData(), 0, 0);

		// シェーダーにコンスタントバッファの情報を送る
		ID3D11Buffer* constant_buffer = graphics_->GetConstantBuffer();
		context->VSSetConstantBuffers(0, 1, &constant_buffer);
		context->PSSetConstantBuffers(0, 1, &constant_buffer);


		if (m_MaterialLinks.count(mesh.m_MaterialName) > 0)
		{
			graphics_->SetTexture(m_MaterialLinks[mesh.m_MaterialName]);
		}
		else
		{
			graphics_->SetTexture(nullptr);
		}


		// 描画
		context->DrawIndexed(mesh.m_Indices.size(), 0, 0);
	}

}

void FbxModel::Play(std::string animName_)
{
	m_PlayMotion = animName_;
	m_Frame = 0.0f;
}

void FbxModel::Animate(float sec_)
{
	m_Frame += sec_ * 60.0f;
	if (m_Frame >= m_Motion[m_PlayMotion].FrameNum - 1)
	{
		m_Frame = 0.0f;
	}
}

bool FbxModel::AddMesh(const char* fileName_, DirectX::XMFLOAT3 pos_, DirectX::XMFLOAT3 scale_, DirectX::XMFLOAT3 degree_, const char* boneName_)
{
	// メッシュ追加前のメッシュの数を保存
	int before_mesh_num = m_MeshList.size();
	int after_mesh_num = 0;

	// メッシュの読み込み
	if (Load(fileName_, DirectGraphics::GetInstance()->GetDevice(), DirectGraphics::GetInstance()->GetVertexShader()) == false) return false;
	// メッシュを追加した後のメッシュの数を保存
	after_mesh_num = m_MeshList.size();

	if (before_mesh_num == after_mesh_num) return false;

	int bone_idx = -1;
	if (boneName_ != nullptr)
	{
		bone_idx = FindBoone(boneName_);
	}

	FbxAMatrix trans;
	trans.SetT(FbxVector4(pos_.x, pos_.y, pos_.z, 1));
	//trans.SetS(FbxVector4(2, 2, 2, 1));
	//trans.SetR(FbxVector4(90, 0, 0, 1));

	for (int i = before_mesh_num; i < after_mesh_num; ++i)
	{
		for (int v = 0; v < m_MeshList[i].m_Vertices.size(); ++v)
		{
			FbxVector4 vertex = FbxVector4(m_MeshList[i].m_Vertices[v].Pos.x,
				m_MeshList[i].m_Vertices[v].Pos.y,
				m_MeshList[i].m_Vertices[v].Pos.z, 1);
			vertex = trans.MultT(vertex);
			m_MeshList[i].m_Vertices[v].Pos.x = vertex[0];	// X
			m_MeshList[i].m_Vertices[v].Pos.y = vertex[1];	// Y
			m_MeshList[i].m_Vertices[v].Pos.z = vertex[2];	// Z

			if (bone_idx != 0)
			{
				m_MeshList[i].m_Vertices[v].Index[0] = bone_idx;
				m_MeshList[i].m_Vertices[v].Weight[0] = 1.0f;
			}
		}
	}

	if (CreateVertexBuffer(DirectGraphics::GetInstance()->GetDevice()) == false)
	{
		return false;
	}
	if (CreateIndexBuffer(DirectGraphics::GetInstance()->GetDevice()) == false)
	{
		return false;
	}

	return true;
}

void FbxModel::LoadMaterial(FbxSurfaceMaterial* material_)
{
	enum class MaterialList
	{
		Ambient,
		Diffuse,
		Specular,
		MaterialMax,
	};

	ObjMaterial entry_material;

	/*
		プロパティの値を取得
	*/
	FbxDouble3  colors[static_cast<int>(MaterialList::MaterialMax)];
	FbxDouble   factors[static_cast<int>(MaterialList::MaterialMax)] = { 0 };
	FbxProperty prop = material_->FindProperty(FbxSurfaceMaterial::sAmbient);

	if (material_->GetClassId().Is(FbxSurfaceLambert::ClassId))
	{
		const char* element_check_list[] =
		{
			FbxSurfaceMaterial::sAmbient,
			FbxSurfaceMaterial::sDiffuse,
			FbxSurfaceMaterial::sSpecular,
		};

		const char* factor_check_list[] =
		{
			FbxSurfaceMaterial::sAmbientFactor,
			FbxSurfaceMaterial::sDiffuseFactor,
			FbxSurfaceMaterial::sSpecularFactor,
		};

		for (int i = 0; i < 3; ++i)
		{
			prop = material_->FindProperty(element_check_list[i]);
			if (prop.IsValid())
			{
				colors[i] = prop.Get<FbxDouble3>();
			}
			else
			{
				colors[i] = FbxDouble3(1.0, 1.0, 1.0);
			}

			prop = material_->FindProperty(factor_check_list[i]);
			if (prop.IsValid())
			{
				factors[i] = prop.Get<FbxDouble>();
			}
			else
			{
				factors[i] = 1.0;
			}
		}
	}

	// 各プロパティのカラー情報を保存
	for (int i = 0; i < 3; ++i)
	{
		entry_material.Ambient[i]  = colors[static_cast<int>(MaterialList::Ambient)].mData[i];
		entry_material.Diffuse[i]  = colors[static_cast<int>(MaterialList::Diffuse)].mData[i];
		entry_material.Specular[i] = colors[static_cast<int>(MaterialList::Specular)].mData[i];
	}
	// 各プロパティのファクター情報を取得
	entry_material.Ambient[3]  = static_cast<float>(factors[static_cast<int>(MaterialList::Ambient)]);
	entry_material.Diffuse[3]  = static_cast<float>(factors[static_cast<int>(MaterialList::Diffuse)]);
	entry_material.Specular[3] = static_cast<float>(factors[static_cast<int>(MaterialList::Specular)]);
	// マテリアルを追加
	m_Materials[material_->GetName()] = entry_material;


	/*
		テクスチャの取得
	*/
	prop = material_->FindProperty(FbxSurfaceMaterial::sDiffuse);

	FbxFileTexture* texture = nullptr;
	std::string keyword;
	int texture_num = prop.GetSrcObjectCount<FbxFileTexture>();
	if (texture_num > 0)
	{
		// FbxFileTextureを取得
		texture = prop.GetSrcObject<FbxFileTexture>(0);
	}
	else
	{
		int layer_num = prop.GetSrcObjectCount<FbxLayeredTexture>();
		if (layer_num > 0)
		{
			texture = prop.GetSrcObject<FbxFileTexture>(0);
		}
	}
	if (texture != nullptr && LoadTexute(DirectGraphics::GetInstance()->GetDevice(), texture, keyword) == true)
	{
		m_MaterialLinks[material_->GetName()] = m_Textures[keyword];
	}

	const FbxImplementation* implementation = GetImplementation(material_, FBXSDK_IMPLEMENTATION_CGFX);
	if (implementation == nullptr)return;
	const FbxBindingTable* root_table = implementation->GetRootTable();
	size_t entry_count = root_table->GetEntryCount();
	for (size_t i = 0; i < entry_count; ++i)
	{
		const FbxBindingTableEntry& entry = root_table->GetEntry(i);
		const char* name = entry.GetSource();

		FbxProperty prop = material_->FindPropertyHierarchical(name);
		int tex_count = prop.GetSrcObjectCount<FbxFileTexture>();

		for (int j = 0; j < tex_count; ++j)
		{
			texture = prop.GetSrcObject<FbxFileTexture>(j);
			if (texture != nullptr && LoadTexute(DirectGraphics::GetInstance()->GetDevice(), texture, keyword) == true)
			{
				m_MaterialLinks[material_->GetName()] = m_Textures[keyword];
			}
		}
	}
}

void FbxModel::LoadIndices(MeshData& meshData_, FbxMesh* mesh_)
{
	// ポリゴン数の取得
	int polygon_count = mesh_->GetPolygonCount();
	// 時計周りに頂点を作りたいので、頂点番号の最初と最後を入れ替えて保存する
	for (int i = 0; i < polygon_count; ++i)
	{
		meshData_.m_Indices.push_back(i * 3 + 2);
		meshData_.m_Indices.push_back(i * 3 + 1);
		meshData_.m_Indices.push_back(i * 3);
	}
}

void FbxModel::LoadVertices(MeshData& meshData_, FbxMesh* mesh_)
{
	// 頂点座標配列を取得
	FbxVector4* vertices = mesh_->GetControlPoints();
	// 頂点番号配列を取得
	int* indices = mesh_->GetPolygonVertices();
	// ポリゴン頂点インデックス数
	int polygon_vertex_count = mesh_->GetPolygonVertexCount();

	FbxAMatrix gm = mesh_->GetNode()->EvaluateGlobalTransform();

	std::vector<FbxVector4> list;

	// 頂点変換
	for (int v = 0; v < mesh_->GetControlPointsCount(); ++v)
	{
		FbxVector4 vec;
		vec = gm.MultT(vertices[v]);
		list.push_back(vertices[v]);
	}


	for (int i = 0; i < polygon_vertex_count; ++i)
	{
		CVertex vertex;
		// インデックスバッファ
		int index = indices[i];

		//
		vertex.Pos.x = (float)-list[index][0];
		vertex.Pos.y = (float)list[index][1];
		vertex.Pos.z = (float)list[index][2];
		meshData_.m_Vertices.emplace_back(vertex);
	}
}

void FbxModel::LoadNormals(MeshData& meshData_, FbxMesh* mesh_)
{
	FbxArray<FbxVector4> normals;
	// 法線リストを取得
	mesh_->GetPolygonVertexNormals(normals);

	// 法線設定
	for (int i = 0; i < normals.Size(); ++i)
	{
		meshData_.m_Vertices[i].Normal.x = (float)-normals[i][0];
		meshData_.m_Vertices[i].Normal.y = (float)normals[i][1];
		meshData_.m_Vertices[i].Normal.z = (float)normals[i][2];
	}
}

void FbxModel::LoadVertexColors(MeshData& meshData_, FbxMesh* mesh_)
{
	// 頂点colorの取得
	// Meshが持っている頂点colorの数を返す
	int color_count = mesh_->GetElementVertexColorCount();
	if (color_count == 0) return;

	// 頂点カラーがあった場合、取得する
	FbxGeometryElementVertexColor* color_buffer = mesh_->GetElementVertexColor(0);
	if (color_buffer == nullptr) return;

	/*
		EMappingModeとEReferenceModeを取得する
		この二つのデータがあれば設定される対象の情報や
		参照方法が分かる。
	*/
	FbxLayerElement::EMappingMode   mapping_mode = color_buffer->GetMappingMode();
	FbxLayerElement::EReferenceMode reference_mode = color_buffer->GetReferenceMode();

	// 頂点にカラーが設定されている場合
	if (mapping_mode == FbxLayerElement::eByPolygonVertex)
	{
		// 参照方法 -> インデックスバッファを介して参照する
		if (reference_mode == FbxLayerElement::eIndexToDirect)
		{
			// 頂点カラーバッファの取得
			FbxLayerElementArrayTemplate<FbxColor>& colors = color_buffer->GetDirectArray();
			// 頂点カラーの頂点番号の取得
			FbxLayerElementArrayTemplate<int>& indeces = color_buffer->GetIndexArray();

			for (int i = 0; i < indeces.GetCount(); ++i)
			{
				int id = indeces.GetAt(i);
				FbxColor color = colors.GetAt(id);
				meshData_.m_Vertices[i].Color.x = color.mRed;
				meshData_.m_Vertices[i].Color.y = color.mGreen;
				meshData_.m_Vertices[i].Color.z = color.mBlue;
				meshData_.m_Vertices[i].Color.w = color.mAlpha;
			}
		}
	}
}

void FbxModel::LoadMaterialNames(MeshData& meshData_, FbxMesh* mesh_)
{
	// マテリアルが存在するか調べる
	if (mesh_->GetElementMaterialCount() == 0)
	{
		meshData_.m_MaterialName = "";
		return;
	}

	// マテリアル情報を取得
	FbxLayerElementMaterial* material = mesh_->GetElementMaterial(0);
	int index = material->GetIndexArray().GetAt(0);
	FbxSurfaceMaterial* surface_material = mesh_->GetNode()->GetSrcObject<FbxSurfaceMaterial>(index);

	if (surface_material != nullptr)
	{
		meshData_.m_MaterialName = surface_material->GetName();
	}
	else
	{
		meshData_.m_MaterialName = "";
	}
}

void FbxModel::LoadUV(MeshData& meshData_, FbxMesh* mesh_)
{
	FbxStringList uvset_names;
	mesh_->GetUVSetNames(uvset_names);

	// UV値の取得
	FbxArray<FbxVector2> uv_buffer;
	mesh_->GetPolygonVertexUVs(uvset_names.GetStringAt(0), uv_buffer);

	for (int i = 0; i < uv_buffer.Size(); ++i)
	{
		FbxVector2& uv = uv_buffer[i];

		// 左下原点になっているので、左上原点にする
		meshData_.m_Vertices[i].TexturePos.x = static_cast<float>(uv[0]);
		meshData_.m_Vertices[i].TexturePos.y = static_cast<float>(1.0 - uv[1]);
	}
}

void FbxModel::LoadBones(MeshData& meshData_, FbxMesh* mesh_)
{
	int skin_num = mesh_->GetDeformerCount(FbxDeformer::eSkin);
	if (skin_num <= 0) return;

	int vertex_num = meshData_.m_Vertices.size();
	FbxSkin* skin = static_cast<FbxSkin*>(mesh_->GetDeformer(0, FbxDeformer::eSkin));

	// ボーン数を取得
	int bone_num = skin->GetClusterCount();
	// ボーンの取得
	for (int b = 0; b < bone_num; ++b)
	{
		FbxCluster* cluster = skin->GetCluster(b);
		FbxAMatrix trans;
		cluster->GetTransformMatrix(trans);
		trans.mData[0][1] *= -1;
		trans.mData[0][2] *= -1;
		trans.mData[1][0] *= -1;
		trans.mData[2][0] *= -1;
		trans.mData[3][0] *= -1;

		// ボーンの名前を取得
		const char* bone_name = cluster->GetLink()->GetInitialName();

		Bone* bone;
		int bone_no = FindBoone(bone_name);
		if (bone_no != -1)
		{
			bone = &m_Bone[bone_no];
		}
		else
		{
			bone_no = m_BoneNum;
			bone = &m_Bone[bone_no];
			m_BoneNum++;

			strcpy_s(bone->Name, bone_name);

			// オフセット行列の作成
			FbxAMatrix link_mat;
			cluster->GetTransformLinkMatrix(link_mat);
			link_mat.mData[0][1] *= -1;
			link_mat.mData[0][2] *= -1;
			link_mat.mData[1][0] *= -1;
			link_mat.mData[2][0] *= -1;
			link_mat.mData[3][0] *= -1;

			FbxAMatrix offset = link_mat.Inverse() * trans;
			FbxDouble* offset_mat = (FbxDouble*)offset;

			bone->Offset = DirectX::XMMatrixSet(
				offset_mat[0], offset_mat[1], offset_mat[2], offset_mat[3],
				offset_mat[4], offset_mat[5], offset_mat[6], offset_mat[7],
				offset_mat[8], offset_mat[9], offset_mat[10], offset_mat[11],
				offset_mat[12], offset_mat[13], offset_mat[14], offset_mat[15]);
		}

		// ウェイトの読み込み
		int weight_num = cluster->GetControlPointIndicesCount();
		int* weight_indices = cluster->GetControlPointIndices();
		double* weight = cluster->GetControlPointWeights();

		int* index = mesh_->GetPolygonVertices();

		for (int i = 0; i < weight_num; ++i)
		{
			int weight_id = weight_indices[i];
			for (int vtx_i = 0; vtx_i < vertex_num; ++vtx_i)
			{
				// 頂点番号が一致しなければコンテニュー
				if (index[vtx_i] != weight_id) continue;

				//
				int weight_count;
				for (weight_count = 0; weight_count < 4; ++weight_count)
				{
					if (meshData_.m_Vertices[vtx_i].Weight[weight_count] <= 0.0f) break;
				}
				if (4 <= weight_count) continue;

				//meshData_.m_Vertices[vtx_i].Index[weight_count] = bone_no;
				//meshData_.m_Vertices[vtx_i].Weight[weight_count] = static_cast<float>(weight[i]);

				// ボーンの影響度が大きいものを4つ選ぶ
				if (meshData_.m_Vertices[vtx_i].Weight[weight_count] < static_cast<float>(weight[i]))
				{
					meshData_.m_Vertices[vtx_i].Index[weight_count] = bone_no;
					meshData_.m_Vertices[vtx_i].Weight[weight_count] = static_cast<float>(weight[i]);
				}
			}
		}
	}

	// ウェイト正規化
	for (int vtx_i = 0; vtx_i < vertex_num; ++vtx_i)
	{
		float n = 0;

		int weight_count;
		for (weight_count = 0; weight_count < 4; weight_count++)
		{
			if (meshData_.m_Vertices[vtx_i].Weight[weight_count] <= 0.0f) break;

			n += meshData_.m_Vertices[vtx_i].Weight[weight_count];
		}

		for (weight_count = 0; weight_count < 4; weight_count++)
		{
			meshData_.m_Vertices[vtx_i].Weight[weight_count] /= n;
		}
	}
}

void FbxModel::LoadKeyFrame(std::string keyword_, int bone_, FbxNode* boneNode_)
{
	Motion* motion = &m_Motion[keyword_];
	motion->Key[bone_].resize(motion->FrameNum);

	double time = static_cast<double>(m_StartFrame * (1.0 / 60.0));
	FbxTime T;
	FbxVector4 trans;
	for (UINT f = 0; f < motion->FrameNum; ++f)
	{
		T.SetSecondDouble(time);

		FbxAMatrix m = boneNode_->EvaluateGlobalTransform(T);
		m.mData[0][1] *= -1; // _12
		m.mData[0][2] *= -1; // _13
		m.mData[1][0] *= -1; // _21
		m.mData[2][0] *= -1; // _31
		m.mData[3][0] *= -1; // _41

		FbxDouble* mat = static_cast<FbxDouble*>(m);
		motion->Key[bone_][f] = DirectX::XMMatrixSet(
			mat[0], mat[1], mat[2], mat[3],
			mat[4], mat[5], mat[6], mat[7],
			mat[8], mat[9], mat[10], mat[11],
			mat[12], mat[13], mat[14], mat[15]
		);
		time += 1.0 / 60.0;


		trans += m.GetT();
	}
	trans /= motion->FrameNum;
}

bool FbxModel::LoadTexute(ID3D11Device* device_, FbxFileTexture* texture_, std::string& keyword_)
{
	if (texture_ == nullptr) return false;

	// ファイル名を取得
	std::string file_path = texture_->GetRelativeFileName();

	// ファイル分解
	char buffer[256];
	ZeroMemory(buffer, sizeof(char) * 256);
	memcpy(buffer, file_path.c_str(), sizeof(char) * 256);

	Replace('\\', '/', buffer);
	std::string replace_file_name = buffer;

	// /で分解
	std::vector<std::string> split_list = Split(buffer, '/');

	std::string root_path = "Res/Texture/";
	std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> cv;
	std::wstring wstr_file_name = cv.from_bytes(root_path + split_list[split_list.size() - 1]);

	char* file_name;
	size_t size = 0;
	FbxUTF8ToAnsi(split_list[split_list.size() - 1].c_str(), file_name, &size);

	const char* extension = "";
	DirectX::TexMetadata  metadata;
	DirectX::ScratchImage image;
	HRESULT hr;

	for (size_t i = strlen(file_name); i != 0; --i)
	{
		if (file_name[i - 1] == '.') extension = &file_name[i];
	}

	// DDSファイルの読み込み
	if (strcmp(extension, "dds") == 0)
	{
		hr = DirectX::LoadFromDDSFile(wstr_file_name.c_str(), DirectX::DDS_FLAGS::DDS_FLAGS_NONE, &metadata, image);
	}
	// TGAファイルの読み込み
	else if (strcmp(extension, "tga") == 0)
	{
		hr = DirectX::LoadFromTGAFile(wstr_file_name.c_str(), &metadata, image);
	}
	// WICファイル(bmp,jpg,png)の読み込み
	else
	{
		hr = DirectX::LoadFromWICFile(wstr_file_name.c_str(), DirectX::WIC_FLAGS::WIC_FLAGS_NONE, &metadata, image);
	}

	if (FAILED(hr))
	{
		FbxFree(file_name);
		return false;
	}


	if (FAILED(DirectX::CreateShaderResourceView(
		device_,
		image.GetImages(),
		image.GetImageCount(),
		metadata,
		&m_Textures[file_name])))
	{
		FbxFree(file_name);
		return false;
	}

	keyword_ = file_name;
	FbxFree(file_name);

	return true;
}

int FbxModel::FindBoone(const char* boneName_)
{
	for (UINT i = 0; i < m_BoneNum; i++)
	{
		if (strcmp(m_Bone[i].Name, boneName_) == 0)
		{
			return (int)i;
		}
	}
	return -1;
}

bool FbxModel::CreateVertexBuffer(ID3D11Device* device_)
{
	for (auto& mesh : m_MeshList)
	{
		//頂点バッファ作成
		D3D11_BUFFER_DESC buffer_desc;
		buffer_desc.ByteWidth = sizeof(CVertex) * mesh.m_Vertices.size();	// バッファのサイズ
		buffer_desc.Usage = D3D11_USAGE_DEFAULT;				// 使用方法
		buffer_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;		// BIND設定
		buffer_desc.CPUAccessFlags = 0;							// リソースへのCPUのアクセス権限についての設定
		buffer_desc.MiscFlags = 0;								// リソースオプションのフラグ
		buffer_desc.StructureByteStride = 0;					// 構造体のサイズ

		D3D11_SUBRESOURCE_DATA sub_resource;
		sub_resource.pSysMem          = &mesh.m_Vertices[0];	// バッファの中身の設定
		sub_resource.SysMemPitch      = 0;						// textureデータを使用する際に使用するメンバ
		sub_resource.SysMemSlicePitch = 0;						// textureデータを使用する際に使用するメンバ

		// バッファ作成
		if (FAILED(device_->CreateBuffer(
			&buffer_desc,										// バッファ情報
			&sub_resource,										// リソース情報
			&mesh.m_VertexBuffer)))								// 作成されたバッファの格納先
		{
			return false;
		}
	}

	return true;
}

bool FbxModel::CreateIndexBuffer(ID3D11Device* device_)
{
	for (auto& mesh : m_MeshList)
	{
		//頂点バッファ作成
		D3D11_BUFFER_DESC buffer_desc;
		buffer_desc.ByteWidth = (UINT)sizeof(UINT) * mesh.m_Indices.size();	// バッファのサイズ
		buffer_desc.Usage = D3D11_USAGE_DEFAULT;							// 使用方法
		buffer_desc.BindFlags = D3D11_BIND_INDEX_BUFFER;					// BIND設定
		buffer_desc.CPUAccessFlags = 0;										// リソースへのCPUのアクセス権限についての設定
		buffer_desc.MiscFlags = 0;											// リソースオプションのフラグ
		buffer_desc.StructureByteStride = 0;								// 構造体のサイズ

		D3D11_SUBRESOURCE_DATA sub_resource;
		sub_resource.pSysMem = &mesh.m_Indices[0];							// バッファの中身の設定
		sub_resource.SysMemPitch = 0;										// textureデータを使用する際に使用するメンバ
		sub_resource.SysMemSlicePitch = 0;									// textureデータを使用する際に使用するメンバ

		// バッファ作成
		if (FAILED(device_->CreateBuffer(
			&buffer_desc,													// バッファ情報
			&sub_resource,													// リソース情報
			&mesh.m_IndexBuffer)))											// 作成されたバッファの格納先
		{
			return false;
		}
	}

	return true;
}

bool FbxModel::CreateInputLayout(ID3D11Device* device_, VertexShader* vertexShader_)
{
	D3D11_INPUT_ELEMENT_DESC vertex_desc[]{
		{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT,		0,	0,							  D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL",		0, DXGI_FORMAT_R32G32B32_FLOAT,		0,	D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR",		0, DXGI_FORMAT_R32G32B32A32_FLOAT,	0,	D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD",   0, DXGI_FORMAT_R32G32_FLOAT,        0,  D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "BONE_INDEX", 0, DXGI_FORMAT_R32G32B32A32_UINT,   0,  D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "BONE_WEIGHT",0, DXGI_FORMAT_R32G32B32A32_FLOAT,  0,  D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	//頂点レイアウト作成
	if (FAILED(device_->CreateInputLayout(
		vertex_desc,				// レイアウト設定
		ARRAYSIZE(vertex_desc),		// 配列サイズ
		vertexShader_->GetData(),	// レイアウトと関連付ける頂点シェーダのデータ
		vertexShader_->GetSize(),	// レイアウトと関連付ける頂点シェーダのサイズ
		&m_InputLayout)))			// 作成された頂点レイアウトの格納先
	{
		return false;
	}

	return true;
}
