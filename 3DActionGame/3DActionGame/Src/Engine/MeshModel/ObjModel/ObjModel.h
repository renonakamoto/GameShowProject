#ifndef OBJ_MODEL_H_
#define OBJ_MODEL_H_

#include <d3d11.h>
#include <vector>
#include <map>
#include "../../DirectGraphics.h"
#include "../../../Utility/GraphicsUtility.h"
#include "../../../Model/Model.h"


class ObjModel : public Model
{
public:
	ObjModel()
	{
		m_Vertices.clear();
	}

	~ObjModel(){}

	bool Load(const char* fileName_, ID3D11Device* device_, VertexShader* vertex_shader);

	void Render(DirectGraphics* graphics_, DirectX::XMFLOAT3 pos_, DirectX::XMFLOAT3 scale_, DirectX::XMFLOAT3 degree);

	const std::vector<CVertex>* GetVertices() const { return &m_Vertices; }

private:
	/*
		OBJファイルの頂点データをスペース区切りにし、データに追加する
		第一 : 頂点データ格納用変数
		第二 : 解析する文字列
	*/
	void ParseVertex(std::vector<DirectX::XMFLOAT3>& data_, char* buff_);

	void ParseFKeywordTag(std::vector<CVertex>& outCustomVertices_, std::string current_material_name_, std::vector<DirectX::XMFLOAT3>& vertices_, std::vector<DirectX::XMFLOAT3>& textures_, std::vector<DirectX::XMFLOAT3>& normals_, char* buffer_);
	void ParseFKeywordTag(MeshData& outMeshData_, std::string current_material_name_, std::vector<DirectX::XMFLOAT3>& vertices_, std::vector<DirectX::XMFLOAT3>& textures_, std::vector<DirectX::XMFLOAT3>& normals_, char* buffer_);

	void ParseSlashKeywordTag(int* list_, char* buffer_);

	bool LoadMaterialFile(std::vector<std::string> fileList_, std::string filePath_, ID3D11Device* device_);
	bool LoadTexture(std::string keyWord_, std::string fileName_, ID3D11Device* device_);

	bool CreateVertexBuffer(ID3D11Device* device_);
	bool CreateIndexBuffer(ID3D11Device* device_);
	bool CreateInputLayout(ID3D11Device* device, VertexShader* vertex_shader);

private:
	ID3D11Buffer*				 m_VertexBuffer;	// バーテックスバッファ
	std::vector<ID3D11Buffer*>	 m_IndexBuffers;	// インデックスバッファ
	ID3D11InputLayout*			 m_InputLayout;		// 入力レイアウト
	std::vector<CVertex>		 m_Vertices;		// バーテックスバッファ
	std::map < std::string, std::vector<UINT> >		 m_Indices;		// インデックスバッファ
	std::map < std::string, ObjMaterial >			 m_Materials;	// マテリアル
	std::map<std::string, ID3D11ShaderResourceView*> m_Textures;
};

#endif