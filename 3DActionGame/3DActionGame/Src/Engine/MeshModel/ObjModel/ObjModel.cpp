
#include "../../../DirectXTex/DirectXTex.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <codecvt> 
#include <iomanip>
#include <cstdio>
#include <sstream>
#include "../../../Utility/Utility.h"
#include "ObjModel.h"


#if _DEBUG
#pragma comment(lib, "Src/DirectXTex/x64/Debug/DirectXTex.lib")
#else
#pragma comment(lib, "Src/DirectXTex/x64/Release/DirectXTex.lib")
#endif


bool ObjModel::Load(const char* fileName_, ID3D11Device* device_, VertexShader* vertex_shader)
{
    
    FILE* fp = nullptr;
    fopen_s(&fp, fileName_, "r");

    // 読み込みが成功しているかを調べる
    if (fp == nullptr) { return false; }

    std::vector<DirectX::XMFLOAT3> vertices;
    std::vector<DirectX::XMFLOAT3> textures;
    std::vector<DirectX::XMFLOAT3> normals;
    std::string current_mat_name;
    std::vector<std::string> material_list;
    std::map<std::string, MeshData> mesh_data;

    const int line_buffer_length = 1024;
    char line_buffer[line_buffer_length];

    // 1行取得する
    while (fgets(line_buffer, line_buffer_length, fp) != nullptr)
    {
        // コメントなら無視する
        if (line_buffer[0] == '#') continue;

        // 1行の中から、スペースを探しそのポインタを取得する
        char* parse_point = strchr(line_buffer, ' ');
        // もしスペースがなければ無視する
        if (parse_point == nullptr) continue;

        Replace('\n', '\0', line_buffer);


        /*
            v  : 頂点座標データ
            vn : 法線データ
            f  : 面データ
        */

        // 先頭を調べ「v」なら頂点情報なので解析を行う
        if (line_buffer[0] == 'v')
        {
            // 二文字目にアクセスして頂点のデータの種類を調べる
            // 頂点座標
            if (line_buffer[1] == ' ') {

                ParseVertex(vertices, &parse_point[1]);

                // X軸を反転させて座標系を右手系から左手系に変換
                vertices[vertices.size() - 1].x *= -1.0f;
            }
            // テクスチャ座標
            else if (line_buffer[1] == 't') {
                ParseVertex(textures, &parse_point[1]);
                // V軸を反転させる
                textures[textures.size() - 1].y = (1.0f - textures[textures.size() - 1].y);
            }
            // 法線ベクトル
            else if (line_buffer[1] == 'n') {

                ParseVertex(normals, &parse_point[1]);

                // X軸を反転させて座標系を右手系から左手系に変換
                normals[normals.size() - 1].x *= -1.0f;
            }
        }
        // もし「f」なら面情報なので解析を行いインデックスバッファに詰め込む
        else if (line_buffer[0] == 'f')
        {
            Replace('\n', '\0', line_buffer);
            //ParseFKeywordTag(m_Vertices, current_mat_name, vertices, textures, normals, &parse_point[1]);
            ParseFKeywordTag(mesh_data[current_mat_name], current_mat_name, vertices, textures, normals, &parse_point[1]);
        }
        // もし「mtllib」ならマテリアル名なので保存する
        else if (strstr(line_buffer, "mtllib") == line_buffer)
        {
            Replace('\n', '\0', line_buffer);
            material_list.push_back(&line_buffer[strlen("mtllib") + 1]);
        }
        // もし「usemtl」なら所属する属性が変わるので変更する
        else if (strstr(line_buffer, "usemtl") == line_buffer)
        {
            Replace('\n', '\0', line_buffer);
            current_mat_name = &line_buffer[strlen("usemtl") + 1];
            mesh_data[current_mat_name].MaterialName = current_mat_name;
        }
    }

    for (auto& mesh : mesh_data)
    {
        m_MeshList.push_back(mesh.second);            
    }

    fclose(fp);

    char   flie_path[256];
    size_t len = strlen(fileName_);
    size_t path_tail_point = 0;

    for (int i = static_cast<int>(len - 1); i >= 0; i--)
    {
        if (fileName_[i] == '/')
        {
            path_tail_point = i;
            break;
        }
    }

    strncpy_s(flie_path, fileName_, path_tail_point + 1);
    
    if (flie_path != nullptr) {
        if (LoadMaterialFile(material_list, flie_path, device_) == false) return false;
    }

    if (CreateVertexBuffer(device_) == false) return false;
    if (CreateIndexBuffer(device_)  == false) return false;
    if (CreateInputLayout(device_, vertex_shader) == false) return false;

    return true;
}

void ObjModel::Render(DirectGraphics* graphics_, DirectX::XMFLOAT3 pos_, DirectX::XMFLOAT3 scale_, DirectX::XMFLOAT3 degree)
{
    /*
        頂点シェーダの設定
    */
    ID3D11DeviceContext* context = DirectGraphics::GetInstance()->GetContext();
    context->VSSetShader(graphics_->GetSimpleVertexShader()->GetShaderInterface(), NULL, 0);
    /*
        ピクセルシェーダの設定
    */
    context->PSSetShader(graphics_->GetSimplePixelShader()->GetShaderInterface(), NULL, 0);

    UINT strides = sizeof(CVertex);
    UINT offsets = 0;
    for (MeshData& mesh : m_MeshList)
    {
        context->IASetVertexBuffers(0, 1, &mesh.VertexBuffer, &strides, &offsets);
        context->IASetIndexBuffer(mesh.IndexBuffer, DXGI_FORMAT_R32_UINT, 0);

        context->IASetInputLayout(m_InputLayout);

        DirectX::XMMATRIX translate = DirectX::XMMatrixTranslation(pos_.x, pos_.y, pos_.z);
        DirectX::XMMATRIX rotate_x = DirectX::XMMatrixRotationX(DirectX::XMConvertToRadians(degree.x));
        DirectX::XMMATRIX rotate_y = DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(degree.y));
        DirectX::XMMATRIX rotate_z = DirectX::XMMatrixRotationZ(DirectX::XMConvertToRadians(degree.z));
        DirectX::XMMATRIX scale = DirectX::XMMatrixScaling(scale_.x, scale_.y, scale_.z);
        DirectX::XMMATRIX world_matrix = scale * rotate_x * rotate_y * rotate_z * translate;

        // ワールド行列をコンスタントバッファに設定
        DirectX::XMStoreFloat4x4(&graphics_->GetConstantBufferData()->World, DirectX::XMMatrixTranspose(world_matrix));

        // マテリアル設定
        graphics_->SetMaterial(&m_Materials[mesh.MaterialName]);

        // コンスタントバッファの更新
        context->UpdateSubresource(graphics_->GetConstantBuffer(), 0, nullptr, graphics_->GetConstantBufferData(), 0, 0);

        // コンスタントバッファを設定
        ID3D11Buffer* constant_buffer = graphics_->GetConstantBuffer();
        context->VSSetConstantBuffers(0, 1, &constant_buffer);
        context->PSSetConstantBuffers(0, 1, &constant_buffer);

        if (m_Textures.count(m_Materials[mesh.MaterialName].TextureKeyWord) > 0)
        {
            graphics_->SetTexture(m_Textures[m_Materials[mesh.MaterialName].TextureKeyWord]);
        }
        else
        {
            graphics_->SetTexture(nullptr);
        }

        // 描画
        context->DrawIndexed(static_cast<UINT>(mesh.Indices.size()), 0, 0);
    }
}

void ObjModel::ParseVertex(std::vector<DirectX::XMFLOAT3>& data_, char* buff_)
{
    std::vector<std::string> split_strings;
    split_strings = Split(buff_, ' ');
    
    int count = 0;
    float value[3] = { 0.f };

    for (std::string str : split_strings)
    {
        value[count] = static_cast<float>(atof(str.c_str()));
        count++;
    }

    data_.push_back(DirectX::XMFLOAT3(value[0], value[1], value[2]));
}

void ObjModel::ParseFKeywordTag(std::vector<CVertex>& outCustomVertices_, std::string current_material_name_, std::vector<DirectX::XMFLOAT3>& vertices_, std::vector<DirectX::XMFLOAT3>& textures_,  std::vector<DirectX::XMFLOAT3>& normals_, char* buffer_)
{
    const int info_num = 3;
    int vertex_info[info_num] =
    {
        -1,// 頂点座標
        -1,// テクスチャ座標
        -1 // 法線ベクトル
    };

    // 面情報をスペース区切りで分ける
    std::vector<std::string> space_split = Split(buffer_, ' ');

    for (size_t i = 0; i < space_split.size(); ++i)
    {
        CVertex vertex;
        // 「/」毎に分ける
        ParseSlashKeywordTag(vertex_info, (char*)space_split[i].c_str());

        for (int j = 0; j < info_num; ++j)
        {
            if (vertex_info[j] == -1) continue;
            
            int id = vertex_info[j];

            switch (j)
            {
                // 頂点座標
            case 0:
                vertex.Pos = vertices_[id];
                break;

                // テクスチャ座標
            case 1:
                vertex.TexturePos = DirectX::XMFLOAT2(textures_[id].x, textures_[id].y);
                break;

                // 法線ベクトル
            case 2:
                vertex.Normal = normals_[id];
                
                break;
            default:
                break;
            }
        }

        // 頂点リストに追加する
        outCustomVertices_.push_back(vertex);

        // インデックスバッファに追加
        m_Indices[current_material_name_].push_back(static_cast<UINT>(outCustomVertices_.size() - 1));
    }


    size_t size = m_Indices[current_material_name_].size();

    if (space_split.size() > 3)
    {
        int temp = m_Indices[current_material_name_][size - 1];
        m_Indices[current_material_name_][size - 1] = m_Indices[current_material_name_][size - 4];
        m_Indices[current_material_name_][size - 4] = temp;

        temp = m_Indices[current_material_name_][size - 2];
        m_Indices[current_material_name_][size - 2] = m_Indices[current_material_name_][size - 3];
        m_Indices[current_material_name_][size - 3] = temp;

        m_Indices[current_material_name_].push_back(m_Indices[current_material_name_][size - 4]);
        m_Indices[current_material_name_].push_back(m_Indices[current_material_name_][size - 2]);

        return;
    }
    
     //ポリゴンの作成の頂点順番を反転する
    int temp = m_Indices[current_material_name_][size - 1];
    m_Indices[current_material_name_][size - 1] = m_Indices[current_material_name_][size - 3];
    m_Indices[current_material_name_][size - 3] = temp;

}

void ObjModel::ParseFKeywordTag(MeshData& outMeshData_, std::string current_material_name_, std::vector<DirectX::XMFLOAT3>& vertices_, std::vector<DirectX::XMFLOAT3>& textures_, std::vector<DirectX::XMFLOAT3>& normals_, char* buffer_)
{
    const int info_num = 3;
    int vertex_info[info_num] =
    {
        -1,// 頂点座標
        -1,// テクスチャ座標
        -1 // 法線ベクトル
    };

    // 面情報をスペース区切りで分ける
    std::vector<std::string> space_split = Split(buffer_, ' ');

    for (size_t i = 0; i < space_split.size(); ++i)
    {
        CVertex vertex;
        // 「/」毎に分ける
        ParseSlashKeywordTag(vertex_info, (char*)space_split[i].c_str());

        for (int j = 0; j < info_num; ++j)
        {
            if (vertex_info[j] == -1) continue;

            int id = vertex_info[j];

            switch (j)
            {
                // 頂点座標
            case 0:
                vertex.Pos = vertices_[id];
                break;

                // テクスチャ座標
            case 1:
                vertex.TexturePos = DirectX::XMFLOAT2(textures_[id].x, textures_[id].y);
                break;

                // 法線ベクトル
            case 2:
                vertex.Normal = normals_[id];

                break;
            default:
                break;
            }
        }

        // 頂点リストに追加する
        outMeshData_.Vertices.push_back(vertex);

        // インデックスバッファに追加
        outMeshData_.Indices.push_back(static_cast<UINT>(outMeshData_.Vertices.size() - 1));
    }


    size_t size = outMeshData_.Indices.size();

    if (space_split.size() > 3)
    {
        int temp = outMeshData_.Indices[size - 1];
        outMeshData_.Indices[size - 1] = outMeshData_.Indices[size - 4];
        outMeshData_.Indices[size - 4] = temp;

        temp = outMeshData_.Indices[size - 2];
        outMeshData_.Indices[size - 2] = outMeshData_.Indices[size - 3];
        outMeshData_.Indices[size - 3] = temp;

        outMeshData_.Indices.push_back(outMeshData_.Indices[size - 4]);
        outMeshData_.Indices.push_back(outMeshData_.Indices[size - 2]);

        return;
    }

    //ポリゴンの作成の頂点順番を反転する
    UINT temp = outMeshData_.Indices[size - 1];
    outMeshData_.Indices[size - 1] = outMeshData_.Indices[size - 3];
    outMeshData_.Indices[size - 3] = temp;
}

void ObjModel::ParseSlashKeywordTag(int* list_, char* buffer_)
{
    int counter = 0;

    // 「/」で文字列を分解する
    std::vector<std::string> slash_split = Split(buffer_, '/');

    for (std::string str : slash_split)
    {
        if (str.size() > 0)
        {
            list_[counter] = atoi(str.c_str()) - 1;
        }
        counter++;
    }

}

bool ObjModel::LoadMaterialFile(std::vector<std::string> fileList_, std::string filePath_, ID3D11Device* device_)
{
    const int line_buffer_length = 1024;
    char line_buffer[line_buffer_length];

    for (auto mat_file_name : fileList_)
    {
        FILE* fp = nullptr;
        std::string name = filePath_;
        name += mat_file_name;

        fopen_s(&fp, name.c_str(), "r");

        if (fp == nullptr) return false;

        std::string current_material_name = "";

        while (fgets(line_buffer, 1024, fp) != nullptr)
        {
            // マテリアル名
            if (strstr(line_buffer, "newmtl") == line_buffer)
            {
                Replace('\n', '\0', line_buffer);
                current_material_name = &line_buffer[strlen("newmtl") + 1];
            }
            // アンビエント
            else if (strstr(line_buffer, "Ka") == line_buffer)
            {
                Replace('\n', '\0', line_buffer);
                std::vector<std::string> split = Split(&line_buffer[strlen("Ka") + 1], ' ');

                for (size_t i = 0; i < split.size(); ++i) {
                    m_Materials[current_material_name].Ambient[i] = static_cast<float>(atof(split[i].c_str()));
                }
            }
            // ディフューズ
            else if (strstr(line_buffer, "Kd") == line_buffer)
            {
                Replace('\n', '\0', line_buffer);
                std::vector<std::string> split = Split(&line_buffer[strlen("Kd") + 1], ' ');

                for (size_t i = 0; i < split.size(); ++i) {
                    m_Materials[current_material_name].Diffuse[i] = static_cast<float>(atof(split[i].c_str()));
                }
            }
            // スペキュラー
            else if (strstr(line_buffer, "Ks") == line_buffer)
            {
                Replace('\n', '\0', line_buffer);
                std::vector<std::string> split = Split(&line_buffer[strlen("Ks") + 1], ' ');

                for (size_t i = 0; i < split.size(); ++i) {
                    m_Materials[current_material_name].Specular[i] = static_cast<float>(atof(split[i].c_str()));
                }
            }
            // テクスチャ
            else if (strstr(line_buffer, "map_Kd") == line_buffer)
            {
                Replace('\n', '\0', line_buffer);
                std::string texture_name = &line_buffer[strlen("map_Kd") + 1];

                // テクスチャまでのパスを保存
                m_Materials[current_material_name].TextureName = filePath_ + texture_name;
                
                std::vector<std::string> split = Split((char*)texture_name.c_str(), '.');
                if (split.size() > 1)
                {
                    m_Materials[current_material_name].TextureKeyWord = split[0];
                    LoadTexture(split[0], m_Materials[current_material_name].TextureName, device_);
                }

            }

        }
        
        fclose(fp);
    }

    return true;
}

bool ObjModel::LoadTexture(std::string keyWord_, std::string fileName_, ID3D11Device* device_)
{
    // ファイル名を取得
    std::string file_path = fileName_;

    // ファイル分解
    char buffer[256];
    ZeroMemory(buffer, sizeof(char) * 256);
    memcpy(buffer, file_path.c_str(), sizeof(char) * 256);

    Replace('\\', '/', buffer);

    // /で分解
    std::vector<std::string> split_list = Split(buffer, '/');

    std::string root_path = "Res/Textures/";
    std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> cv;
    std::wstring wstr_file_name = cv.from_bytes(root_path + split_list[split_list.size() - 1]);

    const char* extension = "";
    DirectX::TexMetadata  metadata;
    DirectX::ScratchImage image;
    HRESULT hr;

    const char* file_name = split_list[split_list.size() - 1].c_str();

    for (size_t i = strlen(file_name); i != 0; --i)
    {
        if (file_name[i - 1] == '.') extension = &file_name[i];
    }

    ID3D11ShaderResourceView* shader_res_view;
    
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
    
    if (FAILED(hr)) return false;

    hr = DirectX::CreateShaderResourceView(
        device_,
        image.GetImages(),
        image.GetImageCount(),
        metadata,
        &shader_res_view);

    if (FAILED(DirectX::CreateShaderResourceView(
        device_,
        image.GetImages(),
        image.GetImageCount(),
        metadata,
        &shader_res_view)))
    {
        return false;
    }
    
    
    m_Textures[keyWord_] = shader_res_view;

    return true; 
}

bool ObjModel::CreateVertexBuffer(ID3D11Device* device_)
{
    for (MeshData& mesh : m_MeshList)
    {
        // 頂点バッファの作成
        D3D11_BUFFER_DESC buffer_desc;
        // バッファの大きさ
        buffer_desc.ByteWidth = static_cast<UINT>(sizeof(CVertex) * mesh.Vertices.size());
        // バッファへの各項目でのアクセス許可を指定
        // 基本的にD3D11_USAGE_DEFAULT
        buffer_desc.Usage = D3D11_USAGE_DEFAULT;
        // バインドの方法
        // 頂点バッファやコンスタントバッファとして使用することを決める
        buffer_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
        // リソースに対してのCPUアクセス方法
        // 0を指定すればCPUアクセスが不要という設定
        buffer_desc.CPUAccessFlags = 0;
        // その他のオプション
        // 不要なら0
        buffer_desc.MiscFlags = 0;
        // 構造体のサイズ
        // バッファを構造体として確保する場合に使用
        // 0を指定してもOK
        buffer_desc.StructureByteStride = 0;

        /*
            リソースの情報を設定する構造体
            上記のD3D11_BUFFER_DESCとセットになっていて、
            作成したバッファの初期化データの指定方法として使われる
        */
        D3D11_SUBRESOURCE_DATA sub_resource_data;
        // バッファを初期化するデータを指定
        // 頂点バッファなら頂点構造体の配列
        // インデックスバッファならインデックスを保存したデータの配列
        // などなど
        sub_resource_data.pSysMem = &mesh.Vertices[0];
        // メモリのピッチ
        // 2Dまたは3Dテクスチャの場合に使用する
        sub_resource_data.SysMemPitch = 0;
        // 深度レベル
        // 2Dまたは3Dテクスチャの場合に使用する
        sub_resource_data.SysMemSlicePitch = 0;


        /*
        * D3D11_BUFFER_DESCとD3D11_SUBRESOURCE_DATAの情報をもとにバッファを作成する
        */
        if (FAILED(device_->CreateBuffer(&buffer_desc, &sub_resource_data, &mesh.VertexBuffer)))
        {
            return false;
        }
    }

    return true;
}

bool ObjModel::CreateIndexBuffer(ID3D11Device* device_)
{
    for (MeshData& mesh : m_MeshList)
    {
        D3D11_BUFFER_DESC index_buffer_desc;
        index_buffer_desc.ByteWidth = static_cast<UINT>(sizeof(UINT) * mesh.Indices.size());
        index_buffer_desc.Usage = D3D11_USAGE_DEFAULT;
        index_buffer_desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
        index_buffer_desc.CPUAccessFlags = 0;
        index_buffer_desc.MiscFlags = 0;
        index_buffer_desc.StructureByteStride = 0;

        D3D11_SUBRESOURCE_DATA index_init_data;
        index_init_data.pSysMem = &mesh.Indices[0];
        index_init_data.SysMemPitch = 0;
        index_init_data.SysMemSlicePitch = 0;


        if (FAILED(device_->CreateBuffer(&index_buffer_desc, &index_init_data, &mesh.IndexBuffer)))
        {
            return false;
        }
    }

    return true;
}

bool ObjModel::CreateInputLayout(ID3D11Device* device, VertexShader* vertex_shader)
{
    D3D11_INPUT_ELEMENT_DESC vertex_desc[]{
        { "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT,		0,	0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "NORMAL",		0, DXGI_FORMAT_R32G32B32_FLOAT,		0,	D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "TEXTURE",    0, DXGI_FORMAT_R32G32_FLOAT,        0,  D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    };

    //頂点レイアウト作成
    if (FAILED(device->CreateInputLayout(
        vertex_desc,				// レイアウト設定
        ARRAYSIZE(vertex_desc),		// 配列サイズ
        vertex_shader->GetData(),	// レイアウトと関連付ける頂点シェーダのデータ
        vertex_shader->GetSize(),	// レイアウトと関連付ける頂点シェーダのサイズ
        &m_InputLayout)))			// 作成された頂点レイアウトの格納先
    {
        return false;
    }

    return true;
}
