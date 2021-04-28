#ifndef OBJ_MODEL_H_
#define OBJ_MODEL_H_

#include <d3d11.h>
#include <vector>
#include <map>
#include "../../Graphics/DirectGraphics.h"
#include "../../../Utility/GraphicsUtility.h"
#include "../Model.h"

/**
* @brief オブジェファイルの読み込み描画を行うクラス
*/
class ObjModel : public Model
{
public:
	/**
	* @brief コンストラクタ
	*/
	ObjModel() :
		m_InputLayout(nullptr)	
	{}

	/**
	* @brief デストラクタ
	*/
	~ObjModel()
	{}

	/**
	* @fn bool LoadTexute(ID3D11Device* device_, FbxFileTexture* texture_, std::string& keyword_)
	* @brief テクスチャ読み込み関数
	* @param[in] device_ デバイス
	* @param[in] texture_ テクスチャ情報
	* @param[out] keyword_ 保存したテクスチャのキーワード
	* @return bool 成功したかどうかを真偽で返す
	*/
	bool Load(const char* fileName_);

	/**
	* @fn bool LoadTexute(ID3D11Device* device_, FbxFileTexture* texture_, std::string& keyword_)
	* @brief テクスチャ読み込み関数
	* @param[in] device_ デバイス
	* @param[in] texture_ テクスチャ情報
	* @param[out] keyword_ 保存したテクスチャのキーワード
	* @return bool 成功したかどうかを真偽で返す
	*/
	void Render(DirectX::XMFLOAT3 pos_, DirectX::XMFLOAT3 scale_, DirectX::XMFLOAT3 degree);

private:
	/*
		OBJファイルの頂点データをスペース区切りにし、データに追加する
		第一 : 頂点データ格納用変数
		第二 : 解析する文字列
	*/
	void ParseVertex(std::vector<DirectX::XMFLOAT3>& data_, char* buff_);

	void ParseFKeywordTag(MeshData& outMeshData_, std::string current_material_name_, std::vector<DirectX::XMFLOAT3>& vertices_, std::vector<DirectX::XMFLOAT3>& textures_, std::vector<DirectX::XMFLOAT3>& normals_, char* buffer_);

	void ParseSlashKeywordTag(int* list_, char* buffer_);

	bool LoadMaterialFile(std::vector<std::string> fileList_, std::string filePath_, ID3D11Device* device_);
	bool LoadTexture(std::string keyWord_, std::string fileName_, ID3D11Device* device_);

	bool CreateVertexBuffer(ID3D11Device* device_);
	bool CreateIndexBuffer(ID3D11Device* device_);
	bool CreateInputLayout(ID3D11Device* device, VertexShader* vertex_shader);

private:
	ComPtr<ID3D11InputLayout>								m_InputLayout;	//! 入力レイアウト
	std::map <std::string, ObjMaterial>						m_Materials;	//! マテリアル
	std::map<std::string, ComPtr<ID3D11ShaderResourceView>> m_Textures;		//! テクスチャ
};

#endif