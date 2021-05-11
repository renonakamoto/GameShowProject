#include <codecvt>
#include "../../../DirectXTex/DirectXTex.h"
#include "../../Engine.h"
#include "FbxModel.h"
#include "../../../Utility/Utility.h"


#if _DEBUG
#pragma comment(lib, "Src/DirectXTex/x64/Debug/DirectXTex.lib")
#else
#pragma comment(lib, "Src/DirectXTex/x64/Release/DirectXTex.lib")
#endif


bool FbxModel::LoadModel(const char* fileName_)
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
		FBX_SAFE_DESTROY(manager);
		return false;
	}

	// FbxSceneの作成
	// Importerによって分解されたfbxのデータを保存するためのクラス
	FbxScene* fbx_scene = FbxScene::Create(manager, "");
	if (fbx_scene == nullptr) {
		// Sceneの作成失敗
		FBX_SAFE_DESTROY(manager);
		return false;
	}

	// FBXファイルを開いて、初期化する
	if (importer->Initialize(fileName_) == false)
	{
		// 読み込み失敗
		FBX_SAFE_DESTROY(manager);

		return false;
	}

	// ImporterでFbxデータを分解してSceneにインポートする
	if (importer->Import(fbx_scene) == false) {
		// インポート失敗
		FBX_SAFE_DESTROY(manager);

		return false;
	}
	// インポートが完了したらインポーターは不要なので破棄する
	FBX_SAFE_DESTROY(importer);
	
	// ジオメトリコンバーターを作成
	FbxGeometryConverter geometry_converter(manager);
	// メッシュに使われているマテリアル単位でメッシュを分割する
	geometry_converter.SplitMeshesPerMaterial(fbx_scene, true);
	// ポリゴンを三角形に変換
	geometry_converter.Triangulate(fbx_scene, true);

	// センチメートル単位にコンバートする
	FbxSystemUnit scene_system_unit = fbx_scene->GetGlobalSettings().GetSystemUnit();
	if (scene_system_unit.GetScaleFactor() != 1.0)
	{
		FbxSystemUnit::cm.ConvertScene(fbx_scene);
	}
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
		m_MeshList.push_back(mesh_data);
	}

	// マネージャーの破棄
	if (manager != nullptr)
	{
		// マネージャーのDestroyを呼べばその他のFBXオブジェクトも破棄される
		FBX_SAFE_DESTROY(manager);
	}

	ID3D11Device* device = GRAPHICS->GetDevice();

	// バーテックスバッファの作成
	if (CreateVertexBuffer(device) == false)
	{
		return false;
	}

	// インデックスバッファの作成
	if (CreateIndexBuffer(device) == false)
	{
		return false;
	}

	// 入力レイアウトの作成
	if (CreateInputLayout(device, GRAPHICS->GetVertexShader()) == false)
	{
		return false;
	}


	// 読み込み成功
	return true;
}

bool FbxModel::LoadMotion(std::string keyword_, const char* fileName_)
{
#pragma region Fbxオブジェクトの作成

	// SDKを管理しているマネージャークラスの生成
	FbxManager* manager = FbxManager::Create();
	if (manager == nullptr) {
		// マネージャーの作成失敗
		return false;
	}

	FbxIOSettings* ios = FbxIOSettings::Create(manager, IOSROOT);
	manager->SetIOSettings(ios);

	// fbxファイルの読み込み、解析をしてくれるクラスの生成
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
		return false;
	}
#pragma endregion


	// アニメーション数を取得
	int anim_count = importer->GetAnimStackCount();

	if (anim_count == 0) {
		FBX_SAFE_DESTROY(importer);
		FBX_SAFE_DESTROY(manager);
		return false;
	}

	for (int i = 0; i < anim_count; ++i)
	{
		// モーション情報を取得
		FbxTakeInfo* take_info = importer->GetTakeInfo(i);
		if (!take_info) continue;

		// モーションの開始時間と終了時間を60Fpsで求める
		FbxLongLong start = take_info->mLocalTimeSpan.GetStart().Get();
		FbxLongLong stop  = take_info->mLocalTimeSpan.GetStop().Get();
		FbxLongLong fps60 = FbxTime::GetOneFrameValue(FbxTime::eFrames60);
		m_StartFrame = static_cast<int>(start / fps60);
		m_Motion[keyword_].FrameNum = static_cast<UINT>((stop - start) / fps60);

		FbxNode* root = fbx_scene->GetRootNode();

		for (UINT b = 0; b < m_BoneNum; ++b)
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
	}
	
	// マネージャーの破棄
	if (manager != nullptr)
	{
		FBX_SAFE_DESTROY(importer);
		// マネージャーのDestroyを呼べばその他のFBXオブジェクトも破棄される
		FBX_SAFE_DESTROY(manager);
	}

	// 読み込み成功
	return true;
}


void FbxModel::Render(DirectX::XMFLOAT3 pos_, DirectX::XMFLOAT3 scale_, DirectX::XMFLOAT3 degree_, std::string motionName_, float frameNum_)
{
	DirectGraphics*      graphics = GRAPHICS;
	ID3D11DeviceContext* context  = graphics->GetContext();
	context->IASetInputLayout(m_InputLayout.Get());

	// ワールド行列の作成
	DirectX::XMMATRIX mat_world, mat_trans, mat_rot_x, mat_rot_y, mat_rot_z, mat_scale;
	mat_trans = DirectX::XMMatrixTranslation(pos_.x, pos_.y, pos_.z);
	mat_rot_x = DirectX::XMMatrixRotationX(DirectX::XMConvertToRadians(degree_.x));
	mat_rot_y = DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(degree_.y));
	mat_rot_z = DirectX::XMMatrixRotationZ(DirectX::XMConvertToRadians(degree_.z));
	mat_scale = DirectX::XMMatrixScaling(scale_.x, scale_.y, scale_.z);
	mat_world = mat_scale * mat_rot_x * mat_rot_y * mat_rot_z * mat_trans;

	// ワールド行列をコンスタントバッファに設定
	DirectX::XMStoreFloat4x4(&graphics->GetConstantBufferData()->World, DirectX::XMMatrixTranspose(mat_world));
	
	UINT strides = sizeof(CVertex);
	UINT offsets = 0U;
	
	for (auto& mesh : m_MeshList)
	{
		// 頂点バッファをバインド
		context->IASetVertexBuffers(0U, 1U, mesh.VertexBuffer.GetAddressOf(), &strides, &offsets);
		// インデックスバッファをバインド
		context->IASetIndexBuffer(mesh.IndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0U);

		// ボーン行列
		Motion* motion = &m_Motion[motionName_];
		if (motion != nullptr)
		{
			if (motion->FrameNum >= 0)
			{
				int f = static_cast<int>(frameNum_);

				for (UINT b = 0; b < m_BoneNum; ++b)
				{
					if (motion->Key[b].empty()) { continue; }

					m_Bone[b].Transform = motion->Key[b][f];
					DirectX::XMMATRIX mat = m_Bone[b].Offset * m_Bone[b].Transform;
					graphics->GetConstBoneBufferData()->Bone[b] = DirectX::XMMatrixTranspose(mat);
				}
			}
		}

		if (m_MaterialLinks.count(mesh.MaterialName) > 0)
		{
			graphics->SetTexture(m_MaterialLinks[mesh.MaterialName].Get());
			// コンスタントバッファにマテリアル情報を保存する
			graphics->SetMaterial(nullptr);
		}
		else
		{
			// コンスタントバッファにマテリアル情報を保存する
			graphics->SetMaterial(&m_Materials[mesh.MaterialName]);
			graphics->SetTexture(nullptr);
		}

		// シェーダーにコンスタントバッファの情報を送る
		ID3D11Buffer* constant_buffer = graphics->GetConstantBuffer();
		context->VSSetConstantBuffers(0U, 1U, &constant_buffer);
		context->PSSetConstantBuffers(0U, 1U, &constant_buffer);

		// ボーン情報を定数バッファにセット
		constant_buffer = graphics->GetConstBoneBuffer();
		context->VSSetConstantBuffers(1U, 1U, &constant_buffer);

		// コンスタントバッファの更新
		graphics->GetContext()->UpdateSubresource(graphics->GetConstantBuffer(), 0U, NULL, graphics->GetConstantBufferData(), 0U, 0U);
		graphics->GetContext()->UpdateSubresource(graphics->GetConstBoneBuffer(), 0U, NULL, graphics->GetConstBoneBufferData(), 0U, 0U);

		// 描画
		context->DrawIndexed(static_cast<UINT>(mesh.Indices.size()), 0U, 0U);
	}

}

bool FbxModel::AddMesh(const char* fileName_, DirectX::XMFLOAT3 pos_,const char* boneName_)
{
	// メッシュ追加前のメッシュの数を保存
	size_t before_mesh_num = m_MeshList.size();
	size_t after_mesh_num  = 0;

	// メッシュの読み込み
	if (LoadModel(fileName_) == false) return false;
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

	for (size_t i = before_mesh_num; i < after_mesh_num; ++i)
	{
		for (int v = 0; v < m_MeshList[i].Vertices.size(); ++v)
		{
			FbxVector4 vertex = FbxVector4(m_MeshList[i].Vertices[v].Pos.x,
				m_MeshList[i].Vertices[v].Pos.y,
				m_MeshList[i].Vertices[v].Pos.z, 1);
			vertex = trans.MultT(vertex);
			m_MeshList[i].Vertices[v].Pos.x = static_cast<float>(vertex[0]); // X
			m_MeshList[i].Vertices[v].Pos.y = static_cast<float>(vertex[1]); // Y
			m_MeshList[i].Vertices[v].Pos.z = static_cast<float>(vertex[2]); // Z

			if (bone_idx != -1)
			{
				m_MeshList[i].Vertices[v].Index[0]  = static_cast<UINT>(bone_idx);
				m_MeshList[i].Vertices[v].Weight[0] = 1.0f;
			}
		}
	}

	if (CreateVertexBuffer(GRAPHICS->GetDevice()) == false)
	{
		return false;
	}
	if (CreateIndexBuffer(GRAPHICS->GetDevice()) == false)
	{
		return false;
	}

	return true;
}

void FbxModel::LoadMaterial(FbxSurfaceMaterial* material_)
{
	if (!material_)return;

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
		entry_material.Ambient[i]  = static_cast<float>(colors[static_cast<int>(MaterialList::Ambient)].mData[i]);
		entry_material.Diffuse[i]  = static_cast<float>(colors[static_cast<int>(MaterialList::Diffuse)].mData[i]);
		entry_material.Specular[i] = static_cast<float>(colors[static_cast<int>(MaterialList::Specular)].mData[i]);
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
	if (texture != nullptr && LoadTexute(GRAPHICS->GetDevice(), texture, keyword) == true)
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
			if (texture != nullptr && LoadTexute(GRAPHICS->GetDevice(), texture, keyword) == true)
			{
				m_MaterialLinks[material_->GetName()] = m_Textures[keyword];
			}
		}
	}
}

void FbxModel::LoadIndices(MeshData& meshData_, FbxMesh* mesh_)
{
	if (!mesh_) return;
	
	// ポリゴン数の取得
	int polygon_count = mesh_->GetPolygonCount();
	// 時計周りに頂点を作りたいので、頂点番号の最初と最後を入れ替えて保存する
	for (int i = 0; i < polygon_count; ++i)
	{
		meshData_.Indices.push_back(i * 3 + 2);
		meshData_.Indices.push_back(i * 3 + 1);
		meshData_.Indices.push_back(i * 3);
	}
}

void FbxModel::LoadVertices(MeshData& meshData_, FbxMesh* mesh_)
{
	if (!mesh_) return;

	// 頂点座標配列を取得
	FbxVector4* vertices = mesh_->GetControlPoints();
	// 頂点番号配列を取得
	int* indices = mesh_->GetPolygonVertices();
	// ポリゴン頂点インデックス数
	int polygon_vertex_count = mesh_->GetPolygonVertexCount();

	// 原点から移動している
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

		// 左手系に変換
		vertex.Pos.x = (float)-list[index][0];
		vertex.Pos.y = (float)list[index][1];
		vertex.Pos.z = (float)list[index][2];
		meshData_.Vertices.emplace_back(vertex);
	}
}

void FbxModel::LoadNormals(MeshData& meshData_, FbxMesh* mesh_)
{
	if (!mesh_) return;

	FbxAMatrix gm = mesh_->GetNode()->EvaluateGlobalTransform();
	FbxAMatrix lm = mesh_->GetNode()->EvaluateLocalTransform();
	
	FbxArray<FbxVector4> normals;
	// 法線リストを取得
	mesh_->GetPolygonVertexNormals(normals);

	// 法線設定
	for (int i = 0; i < normals.Size(); ++i)
	{
		// 左手系に変換
		meshData_.Vertices[i].Normal.x = (float)-normals[i][0];
		meshData_.Vertices[i].Normal.y = (float)normals[i][1];
		meshData_.Vertices[i].Normal.z = (float)normals[i][2];
	}
}

void FbxModel::LoadVertexColors(MeshData& meshData_, FbxMesh* mesh_)
{
	if (!mesh_) return;

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
				meshData_.Vertices[i].Color.x = static_cast<float>(color.mRed  );
				meshData_.Vertices[i].Color.y = static_cast<float>(color.mGreen);
				meshData_.Vertices[i].Color.z = static_cast<float>(color.mBlue );
				meshData_.Vertices[i].Color.w = static_cast<float>(color.mAlpha);
			}
		}
	}
}

void FbxModel::LoadMaterialNames(MeshData& meshData_, FbxMesh* mesh_)
{
	if (!mesh_) return;

	// マテリアルが存在するか調べる
	if (mesh_->GetElementMaterialCount() == 0)
	{
		meshData_.MaterialName = "";
		return;
	}

	// マテリアル情報を取得
	FbxLayerElementMaterial* material = mesh_->GetElementMaterial(0);
	int index = material->GetIndexArray().GetAt(0);
	FbxSurfaceMaterial* surface_material = mesh_->GetNode()->GetSrcObject<FbxSurfaceMaterial>(index);

	if (surface_material != nullptr)
	{
		meshData_.MaterialName = surface_material->GetName();
	}
	else
	{
		meshData_.MaterialName = "";
	}
}

void FbxModel::LoadUV(MeshData& meshData_, FbxMesh* mesh_)
{
	if (!mesh_) return;

	FbxStringList uvset_names;
	mesh_->GetUVSetNames(uvset_names);

	// UV値の取得
	FbxArray<FbxVector2> uv_buffer;
	mesh_->GetPolygonVertexUVs(uvset_names.GetStringAt(0), uv_buffer);

	for (int i = 0; i < uv_buffer.Size(); ++i)
	{
		FbxVector2& uv = uv_buffer[i];

		// 左下原点になっているので、左上原点にする
		meshData_.Vertices[i].TexturePos.x = static_cast<float>(uv[0]);
		meshData_.Vertices[i].TexturePos.y = static_cast<float>(1.0 - uv[1]);
	}
}

void FbxModel::LoadBones(MeshData& meshData_, FbxMesh* mesh_)
{
	int skin_num = mesh_->GetDeformerCount(FbxDeformer::eSkin);
	if (skin_num <= 0) return;

	size_t vertex_num = meshData_.Vertices.size();
	FbxSkin* skin = static_cast<FbxSkin*>(mesh_->GetDeformer(0, FbxDeformer::eSkin));

	// ボーン数を取得
	int bone_num = skin->GetClusterCount();
	// ボーンの取得
	for (int b = 0; b < bone_num; ++b)
	{
		FbxCluster* cluster = skin->GetCluster(b);
		FbxAMatrix trans;
		cluster->GetTransformMatrix(trans);
		// 左手系に変換
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

			// FbxDoubleからfloatにキャストする関数オブジェクト
			auto to_float = [](FbxDouble d_)->float {return static_cast<float>(d_); };

			bone->Offset = DirectX::XMMatrixSet(
				to_float(offset_mat[0]),  to_float(offset_mat[1]),  to_float(offset_mat[2]),  to_float(offset_mat[3]),
				to_float(offset_mat[4]),  to_float(offset_mat[5]),  to_float(offset_mat[6]),  to_float(offset_mat[7]),
				to_float(offset_mat[8]),  to_float(offset_mat[9]),  to_float(offset_mat[10]), to_float(offset_mat[11]),
				to_float(offset_mat[12]), to_float(offset_mat[13]), to_float(offset_mat[14]), to_float(offset_mat[15]));
		}

		// ウェイトの読み込み
		int weight_num = cluster->GetControlPointIndicesCount();
		int* weight_indices = cluster->GetControlPointIndices();
		double* weight = cluster->GetControlPointWeights();

		int* index = mesh_->GetPolygonVertices();

		for (int i = 0; i < weight_num; ++i)
		{
			int weight_id = weight_indices[i];
			for (size_t vtx_i = 0; vtx_i < vertex_num; ++vtx_i)
			{
				// 頂点番号が一致しなければコンテニュー
				if (index[vtx_i] != weight_id) continue;

				int weight_count;
				for (weight_count = 0; weight_count < 4; ++weight_count)
				{
					if (meshData_.Vertices[vtx_i].Weight[weight_count] <= 0.0f) break;
				}
				if (weight_count >= 4)
				{
					for (int x = 0; x < 4; ++x)
					{
						if (meshData_.Vertices[vtx_i].Weight[x] < weight[i])
						{
							weight_count = x;
						}
					}
				}
				if (weight_count >= 4)
				{
					continue;
				}
				meshData_.Vertices[vtx_i].Index[weight_count]  = static_cast<UINT>(bone_no);
				meshData_.Vertices[vtx_i].Weight[weight_count] = static_cast<float>(weight[i]);
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
			if (meshData_.Vertices[vtx_i].Weight[weight_count] <= 0.0f) break;

			n += meshData_.Vertices[vtx_i].Weight[weight_count];
		}

		for (weight_count = 0; weight_count < 4; weight_count++)
		{
			meshData_.Vertices[vtx_i].Weight[weight_count] /= n;
		}
	}
}

void FbxModel::LoadKeyFrame(std::string keyword_, UINT bone_, FbxNode* boneNode_)
{
	Motion* motion = &m_Motion[keyword_];
	motion->Key[bone_].resize(motion->FrameNum);

	double time = static_cast<double>(m_StartFrame * (1.f / 60.f));
	FbxTime t;
	for (UINT f = 0; f < motion->FrameNum; ++f)
	{
		t.SetSecondDouble(time);

		// フレーム時姿勢行列を取得
		FbxAMatrix m = boneNode_->EvaluateGlobalTransform(t);
		// 左手系に変換
		m.mData[0][1] *= -1; // _12
		m.mData[0][2] *= -1; // _13
		m.mData[1][0] *= -1; // _21
		m.mData[2][0] *= -1; // _31
		m.mData[3][0] *= -1; // _41

		// FbxDoubleからfloatにキャストする関数オブジェクト
		auto to_float = [](FbxDouble d_)->float {return static_cast<float>(d_); };
		
		// キーフレームをマトリックスに保存
		FbxDouble* mat = static_cast<FbxDouble*>(m);
		motion->Key[bone_][f] = DirectX::XMMatrixSet(
			to_float(mat[0]),  to_float(mat[1]),  to_float(mat[2]),  to_float(mat[3]),
			to_float(mat[4]),  to_float(mat[5]),  to_float(mat[6]),  to_float(mat[7]),
			to_float(mat[8]),  to_float(mat[9]),  to_float(mat[10]), to_float(mat[11]),
			to_float(mat[12]), to_float(mat[13]), to_float(mat[14]), to_float(mat[15]));

		// フレームを進める
		time += 1.0 / 60.0;
	}
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

	std::string root_path = "Res/Textures/";
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
		m_Textures[file_name].GetAddressOf())))
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
	if (!device_) return false;

	for (auto& mesh : m_MeshList)
	{
		//頂点バッファ作成
		D3D11_BUFFER_DESC buffer_desc;
		buffer_desc.ByteWidth = static_cast<UINT>(sizeof(CVertex) * mesh.Vertices.size());// バッファのサイズ
		buffer_desc.Usage				= D3D11_USAGE_DEFAULT;						      // 使用方法
		buffer_desc.BindFlags			= D3D11_BIND_VERTEX_BUFFER;					      // BIND設定
		buffer_desc.CPUAccessFlags		= 0;										      // リソースへのCPUのアクセス権限についての設定
		buffer_desc.MiscFlags			= 0;										      // リソースオプションのフラグ
		buffer_desc.StructureByteStride = 0;										      // 構造体のサイズ

		D3D11_SUBRESOURCE_DATA init_data;
		init_data.pSysMem			= &mesh.Vertices[0];		// バッファの中身の設定
		init_data.SysMemPitch		= 0;						// textureデータを使用する際に使用するメンバ
		init_data.SysMemSlicePitch	= 0;						// textureデータを使用する際に使用するメンバ

		// バッファ作成
		if (FAILED(device_->CreateBuffer(
			&buffer_desc,										// バッファ情報
			&init_data,										    // リソース情報
			mesh.VertexBuffer.GetAddressOf())))								// 作成されたバッファの格納先
		{
			return false;
		}
	}

	return true;
}

bool FbxModel::CreateIndexBuffer(ID3D11Device* device_)
{
	if (!device_) return false;

	for (auto& mesh : m_MeshList)
	{
		//頂点バッファ作成
		D3D11_BUFFER_DESC buffer_desc;
		buffer_desc.ByteWidth = (UINT)(sizeof(UINT) * mesh.Indices.size());	// バッファのサイズ
		buffer_desc.Usage				= D3D11_USAGE_DEFAULT;				// 使用方法
		buffer_desc.BindFlags			= D3D11_BIND_INDEX_BUFFER;			// BIND設定
		buffer_desc.CPUAccessFlags		= 0;								// リソースへのCPUのアクセス権限についての設定
		buffer_desc.MiscFlags			= 0;								// リソースオプションのフラグ
		buffer_desc.StructureByteStride = 0;								// 構造体のサイズ

		D3D11_SUBRESOURCE_DATA sub_resource;
		sub_resource.pSysMem		  = &mesh.Indices[0];	// バッファの中身の設定

		// バッファ作成
		if (FAILED(device_->CreateBuffer(
			&buffer_desc,			// バッファ情報
			&sub_resource,			// リソース情報
			mesh.IndexBuffer.GetAddressOf())))	// 作成されたバッファの格納先
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
		m_InputLayout.ReleaseAndGetAddressOf())))			// 作成された頂点レイアウトの格納先
	{
		return false;
	}

	return true;
}
