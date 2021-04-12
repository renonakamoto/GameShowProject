#include <stdio.h>

#include "DirectGraphics.h"
#include "Window.h"

#pragma comment(lib,"d3d11.lib")

//#define ENABLE_MASS

bool DirectGraphics::Init()
{
    // デバイスとスワップチェインの作成 
    if (CreateDeviceAndSwapChain() == false)
    {
        return true;
    }

    // レンダーターゲットビューの作成
    if (CreateRenderTargetView() == false)
    {
        return false;
    }

    // デプスビューとステンシルビューの作成
    if (CreateDepthAndStencilView() == false)
    {
        return false;
    }

    // ビューポート設定
    SetUpViewPort();
    
    // シェーダーの作成
    if (CreateShader() == false)
    {
        return false;
    }

    // コンスタントバッファの作成
    if (CreateConstantBuffer() == false)
    {
        return false;
    }

    // テクスチャサンプラの作成
    if (CreateTextureSampler() == false)
    {
        return false;
    }

    


    //// ラスタライザ
    //D3D11_RASTERIZER_DESC rasterizerDesc;
    //ID3D11RasterizerState* state;
    //ZeroMemory(&rasterizerDesc, sizeof(rasterizerDesc));
    //rasterizerDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
    //rasterizerDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
    //rasterizerDesc.FrontCounterClockwise = TRUE;
    //if (FAILED(m_Device->CreateRasterizerState(&rasterizerDesc, &state)))
    //{
    //    return false;
    //}

    //m_Context->RSSetState(state);





    HWND window_handle = FindWindow(Window::ClassName, nullptr);
    RECT rect;
    GetClientRect(window_handle, &rect);

    // View行列設定
    DirectX::XMVECTOR eye = DirectX::XMVectorSet(0.0f, 50.0f, -300.0f, 0.0f);
    DirectX::XMVECTOR focus = DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
    DirectX::XMVECTOR up = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
    DirectX::XMMATRIX view_matrix = DirectX::XMMatrixLookAtLH(eye, focus, up);

    // プロジェクション行列設定
    constexpr float fov = DirectX::XMConvertToRadians(45.0f);
    float aspect = (float)(rect.right - rect.left) / (rect.bottom - rect.top);
    float near_z = 0.1f;
    float far_z = 500000.f;
    DirectX::XMMATRIX proj_matrix = DirectX::XMMatrixPerspectiveFovLH(fov, aspect, near_z, far_z);

    DirectX::XMStoreFloat4x4(&m_ConstantBufferData.View, DirectX::XMMatrixTranspose(view_matrix));
    DirectX::XMStoreFloat4x4(&m_ConstantBufferData.Projection, DirectX::XMMatrixTranspose(proj_matrix));
    DirectX::XMStoreFloat4(&m_ConstantBufferData.CameraPos, eye);

    DirectX::XMStoreFloat4x4(&m_SimpleConstantBufferData.View, DirectX::XMMatrixTranspose(view_matrix));
    DirectX::XMStoreFloat4x4(&m_SimpleConstantBufferData.Projection, DirectX::XMMatrixTranspose(proj_matrix));
    DirectX::XMStoreFloat4(&m_SimpleConstantBufferData.CameraPos, eye);
    // ライト設定
    DirectX::XMVECTOR light = DirectX::XMVector3Normalize(DirectX::XMVectorSet(0.0f, 0.5f, -1.0f, 0.0f));
    DirectX::XMStoreFloat4(&m_SimpleConstantBufferData.LightVector, light);

    // ライトのカラー設定
    m_SimpleConstantBufferData.LightColor = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);

    // ライトの設定
    DirectX::XMStoreFloat4(&m_ConstantBufferData.Light, DirectX::XMVector3Normalize(DirectX::XMVectorSet(0.0f, 0.5f, -1.0f, 0.0f)));
    //DirectX::XMMATRIX mat_rot = DirectX::XMMatrixIdentity();
    //
    //DirectX::XMMATRIX mat   =  DirectX::XMMatrixRotationX(DirectX::XMConvertToRadians(90.f));
    //DirectX::XMMATRIX trans =  DirectX::XMMatrixTranslation(m_ConstantBufferData.Light.x, m_ConstantBufferData.Light.y, m_ConstantBufferData.Light.z);
    //mat = mat * trans;
    //DirectX::XMMATRIX light_view = DirectX::XMMatrixInverse(nullptr, mat);
    //DirectX::XMStoreFloat4x4(&m_ConstantBufferData.LightView, DirectX::XMMatrixTranspose(light_view));

    DirectX::XMMATRIX light_view = DirectX::XMMatrixLookAtLH(
        DirectX::XMVectorSet(m_ConstantBufferData.Light.x, m_ConstantBufferData.Light.y, m_ConstantBufferData.Light.z, 0.0f),
        DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f),
        DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f));

    DirectX::XMStoreFloat4x4(&m_ConstantBufferData.LightView, DirectX::XMMatrixTranspose(light_view));

    m_ConstantBufferData.Attenuation = DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);


    //テクスチャ行列の設定
    ZeroMemory(&m_ConstantBufferData.ClipUV, sizeof(DirectX::XMFLOAT4X4));
    m_ConstantBufferData.ClipUV._11 = 0.5f;
    m_ConstantBufferData.ClipUV._22 = -0.5f;
    m_ConstantBufferData.ClipUV._33 = 1.0f;
    m_ConstantBufferData.ClipUV._41 = 0.5f;
    m_ConstantBufferData.ClipUV._42 = 0.5f;
    m_ConstantBufferData.ClipUV._44 = 1.0f;

    DirectX::XMMATRIX tex_uv = DirectX::XMMatrixSet(
        0.5f, 0, 0, 0,
        0, -0.5f, 0, 0,
        0, 0, 1.0f, 0,
        0.5f, 0.5f, 0, 1.0f);

    DirectX::XMStoreFloat4x4(&m_ConstantBufferData.ClipUV, DirectX::XMMatrixTranspose(tex_uv));

    // ラスタライザ
    D3D11_RASTERIZER_DESC rasterizerDesc;
    ID3D11RasterizerState* state;
    ZeroMemory(&rasterizerDesc, sizeof(rasterizerDesc));
    rasterizerDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
    rasterizerDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
    rasterizerDesc.FrontCounterClockwise = TRUE;
    if (FAILED(m_Device->CreateRasterizerState(&rasterizerDesc, &state)))
    {
        return false;
    }

    m_Context->RSSetState(state);


    return true;
}

void DirectGraphics::Release()
{
    
    if (m_Context != nullptr)
    {
        m_Context->ClearState();
        m_Context->Release();
    }

    if (m_SwapChain != nullptr)
    {
        m_SwapChain->Release();
    }

    if (m_Device != nullptr)
    {
        m_Device->Release();
    }

}

/*
    描画開始関数
*/
void DirectGraphics::StartRendering()
{
    /*
        DirectX11は描画の開始を宣言する必要はないがビューのクリアを毎フレーム
        行わないと描画内容がおかしいことになる
    */

    float clear_color[4] = { 0.0f,0.0f,1.0f,1.0f };

    // レンダーターゲットビューのクリアw
    m_Context->ClearRenderTargetView(
                m_RenderTargetView, // 対象のレンダーターゲットビュー
                clear_color         // クリアするビューのカラー
                );

    // デプスステンシルビューのクリア
    m_Context->ClearDepthStencilView(
                m_DepthStencilView,                      // 対象のビュー
                D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, // クリアフラグ
                1.0f,                                    // 深度クリア値
                0                                        // ステンシルクリア値
                );

    /*
        ビューポートの設定
    */
    HWND window_handle = FindWindow(Window::ClassName, nullptr);
    RECT rect;
    GetClientRect(window_handle, &rect);

    D3D11_VIEWPORT vp;
    vp.Width  = (rect.right - rect.left);
    vp.Height = (rect.bottom - rect.top);
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    vp.TopLeftX = 0.0f;
    vp.TopLeftY = 0.0f;
    m_Context->RSSetViewports(1, &vp);

    /*
       出力先の設定
    */
    m_Context->OMSetRenderTargets(1, &m_RenderTargetView, m_DepthStencilView);

}

/*
    描画終了関数
    バックバッファに書き込んだ情報をフロントバッファに渡す
*/
void DirectGraphics::FinishRendering()
{
    // バックバッファをフロントバッファに送信する   
    m_SwapChain->Present(1, 0);
}

void DirectGraphics::SetUpContext()
{
    /*
    プリミティブの設定
    描画するポリゴンの作成方法を設定する
    */
    m_Context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    /*
        頂点シェーダの設定
    */
    m_Context->VSSetShader(m_VertexShader->GetShaderInterface(), NULL, 0);
    /*
        ピクセルシェーダの設定
    */
    m_Context->PSSetShader(m_PixelShader->GetShaderInterface(), NULL, 0);

    /*
       出力先の設定
   */
    m_Context->OMSetRenderTargets(1, &m_RenderTargetView, m_DepthStencilView);
}

void DirectGraphics::SetTexture(ID3D11ShaderResourceView* texture_)
{
    m_Context->PSSetSamplers(
        0,
        1,
        &m_SamplerState);

    m_Context->PSSetShaderResources(
        0,
        1,
        &texture_);
    
}

void DirectGraphics::SetMaterial(ObjMaterial* material_)
{
    m_ConstantBufferData.MaterialAmbient = DirectX::XMFLOAT4(material_->Ambient[0],
        material_->Ambient[1],
        material_->Ambient[2], 1);
    m_ConstantBufferData.MaterialDiffuse = DirectX::XMFLOAT4(material_->Diffuse[0], material_->Diffuse[1], material_->Diffuse[2], 1);
    m_ConstantBufferData.MaterialSpecular = DirectX::XMFLOAT4(material_->Specular[0], material_->Specular[1], material_->Specular[2], 1);
}

void DirectGraphics::SetUpDxgiSwapChanDesc(DXGI_SWAP_CHAIN_DESC* dxgi)
{
    HWND window_handle = FindWindow(Window::ClassName, nullptr);
    RECT rect;
    GetClientRect(window_handle, &rect);

    // スワップチェイン作成時に必要な設定
    ZeroMemory(dxgi, sizeof(DXGI_SWAP_CHAIN_DESC));
    
    // バッファの数
    dxgi->BufferCount = 1;
    // バッファの横幅
    dxgi->BufferDesc.Width  = static_cast<UINT>(rect.right - rect.left);
    // バッファの縦幅
    dxgi->BufferDesc.Height = static_cast<UINT>(rect.bottom - rect.top);
    // バッファのカラーフォーマット
    dxgi->BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    // リフレッシュレートの分子
    dxgi->BufferDesc.RefreshRate.Numerator   = 60;
    // リフレッシュレートの分母
    dxgi->BufferDesc.RefreshRate.Denominator = 1;
    // スキャンラインの方法
    // バックバッファをフリップしたときにハードウェアがパソコンのモニターに
    // 点をどう描くかを設定する
    // 特に理由がなければデフォルト値であるDXGI_MODE_SCANLINE_ORDER_UNSPECIFIEDでOK
    dxgi->BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
    // ウィンドウのサイズに応じてスケーリングするかどうかの設定
    // スケーリングする場合   DXGI_MODE_SCALING_STRETCHED 
    // スケーリングしない場合 DXGI_MODE_SCALING_CENTERED
    dxgi->BufferDesc.Scaling = DXGI_MODE_SCALING_STRETCHED;
    // バッファの使用方法
    // レンダーターゲットとして使用する場合は、DXGI_USAGE_RENDER_TARGET_OUTPUT 
    // シェーダー入力用として使用する場合はDXGI_USAGE_SHADER_INPUT
    dxgi->BufferUsage  = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    // 出力対象のウィンドウハンドル
    dxgi->OutputWindow = window_handle;
    // マルチサンプリングのサンプル数(未使用は1)
    dxgi->SampleDesc.Count = 1;
    // マルチサンプリングの品質(未使用は0)
    dxgi->SampleDesc.Quality = 0;
    // ウィンドウモード指定
    dxgi->Windowed = true;
    // スワップチェインの動作オプション
    // DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCHを指定した場合
    // フルスクリーンとウィンドウモードの切り替えが可能
    dxgi->Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

}

bool DirectGraphics::CreateDeviceAndSwapChain()
{
#ifdef ENABLE_MASS
    if (FAILED(D3D11CreateDevice(
        nullptr,
        D3D_DRIVER_TYPE_HARDWARE,
        nullptr,
        0,
        nullptr,
        0,
        D3D11_SDK_VERSION,
        &m_Device,
        nullptr,
        &m_Context)))
    {
        return false;
    }


    for (int i = 0; i <= D3D11_MAX_MULTISAMPLE_SAMPLE_COUNT; ++i)
    {
        UINT quality;
        if (SUCCEEDED(m_Device->CheckMultisampleQualityLevels(DXGI_FORMAT_D24_UNORM_S8_UINT, i, &quality)))
        {
            if (0 < quality)
            {
                m_SampleDesc.Count = i;
                m_SampleDesc.Quality = quality - 1;
            }
        }
    }

    // インターフェースを取得
    IDXGIDevice1* dxgi = nullptr;
    if (FAILED(m_Device->QueryInterface(__uuidof(IDXGIDevice1), (void**)&dxgi)))
    {
        return false;
    }

    // アダプターを取得
    IDXGIAdapter* adapter = nullptr;
    if (FAILED(dxgi->GetAdapter(&adapter)))
    {
        return false;
    }

    // ファクトリーを取得
    IDXGIFactory* factory = nullptr;
    adapter->GetParent(__uuidof(IDXGIFactory), (void**)&factory);
    if (factory == nullptr)
    {
        return false;
    }

    DXGI_SWAP_CHAIN_DESC swap_chain_desc;

    HWND window_handle = FindWindow(Window::ClassName, nullptr);
    RECT rect;
    GetClientRect(window_handle, &rect);

    // スワップチェイン作成時に必要な設定
    ZeroMemory(&swap_chain_desc, sizeof(DXGI_SWAP_CHAIN_DESC));

    // バッファの数
    swap_chain_desc.BufferCount = 1;
    // バッファの横幅
    swap_chain_desc.BufferDesc.Width = static_cast<UINT>(rect.right - rect.left);
    // バッファの縦幅
    swap_chain_desc.BufferDesc.Height = static_cast<UINT>(rect.bottom - rect.top);
    // バッファのカラーフォーマット
    swap_chain_desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    // リフレッシュレートの分子
    swap_chain_desc.BufferDesc.RefreshRate.Numerator = 60;
    // リフレッシュレートの分母
    swap_chain_desc.BufferDesc.RefreshRate.Denominator = 1;
    // スキャンラインの方法
    // バックバッファをフリップしたときにハードウェアがパソコンのモニターに
    // 点をどう描くかを設定する
    // 特に理由がなければデフォルト値であるDXGI_MODE_SCANLINE_ORDER_UNSPECIFIEDでOK
    swap_chain_desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
    // ウィンドウのサイズに応じてスケーリングするかどうかの設定
    // スケーリングする場合   DXGI_MODE_SCALING_STRETCHED 
    // スケーリングしない場合 DXGI_MODE_SCALING_CENTERED
    swap_chain_desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
    // バッファの使用方法
    // レンダーターゲットとして使用する場合は、DXGI_USAGE_RENDER_TARGET_OUTPUT 
    // シェーダー入力用として使用する場合はDXGI_USAGE_SHADER_INPUT
    swap_chain_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    // 出力対象のウィンドウハンドル
    swap_chain_desc.OutputWindow = window_handle;
    swap_chain_desc.SampleDesc = m_SampleDesc;
    swap_chain_desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
    // ウィンドウモード指定
    swap_chain_desc.Windowed = true;
    // スワップチェインの動作オプション
    // DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCHを指定した場合
    // フルスクリーンとウィンドウモードの切り替えが可能
    swap_chain_desc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

    if (FAILED(factory->CreateSwapChain(m_Device, &swap_chain_desc, &m_SwapChain)))
    {
        return false;
    }
#else
DXGI_SWAP_CHAIN_DESC swap_chain_desc;
SetUpDxgiSwapChanDesc(&swap_chain_desc);

// 適応されたFutureレベルも取得できる
if (FAILED(D3D11CreateDeviceAndSwapChain(
    // デバイス作成時に使用するビデオアダプタの指定
    // nullptrで既定のアダプタを使用する
    nullptr,
    // ドライバのタイプ
    // D3D_DRIVER_TYPEのいずれかを指定
    // 通常はD3D_DRIVER_TYPE_HARDWAREで問題ない
    D3D_DRIVER_TYPE_HARDWARE,
    // D3D_DRIVER_TYPE_SOFTWARE指定時に使用
    nullptr,
    // ランタイムレイヤーのフラグ指定
    0,
    // D3D_FEATURE_LEVEL指定で自分で定義した配列を指定可能
    nullptr,
    // 上のD3D_FEATURE_LEVEL配列の要素数
    0,
    // SDKバージョン
    D3D11_SDK_VERSION,
    // 設定済みのDXGI_SWAP_CHAIN_DESC
    &swap_chain_desc,
    // 初期化が完了したSwapChainの出力先 
    &m_SwapChain,
    // 初期化が完了したDeviceの出力先 
    &m_Device,
    // 最終的に決定したFutureレベルの出力先
    &m_FeatureLevel,
    // 作成されたコンテキストを受け取るためのID3D11DeviceContextポインタアドレス
    &m_Context)))
{
    return false;
}

#endif


    /*
        D3D11CreateDeviceAndSwapChainを使用するとレンダリング用のContextが作成される
        Contextは描画コマンドの追加、送信などの処理を行う
        CPU側で追加された描画コマンドをGPU側に送信するのが主な役目
        Contextnには「Immediate」と「Deferred」の2種類あり
        Immediateは生成したコマンドを即時実行する
        Deferredは生成した描画コマンドをバッファにためておき、
        実行命令を受けたらたまっているコマンドを実行する
        マルチスレッドによる描画処理に有効とされている

        D3D11CreateDeviceAndSwapChainで作成した場合、Immediateで作成される
    */

    
    return true;
}

bool DirectGraphics::CreateRenderTargetView()
{
    /*
        RenderTargetViewはレンダリングパイプラインからアウトプットされる
        ピクセル情報を保存するViewのことで、このViewの内容をゲーム画面に反映させる。
    */

    // RenderViewはSwapChainがもつバッファを使用して作成するので
    // GetBufferを使用してバッファを取得する
    ID3D11Texture2D* back_buffer;
    if (FAILED(m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&back_buffer)))
    {
        return false;
    }
    
    // RenderTargetViewの作成
    if (FAILED(m_Device->CreateRenderTargetView(back_buffer, nullptr, &m_RenderTargetView)))
    {
        return false;
    }

    // これ以降バッファを使用しないので、解放しておく
    back_buffer->Release();
    
    return true;
}

bool DirectGraphics::CreateDepthAndStencilView()
{
    /*
        CreateTexture2Dで作成されたテクスチャをバッファとして使用するので
        D3D11_TEXTURE2D_DESCでテクスチャの設定を行う
    */
    
    HWND window_handle = FindWindow(Window::ClassName, nullptr);
    RECT rect;
    GetClientRect(window_handle, &rect);
    
    // 深度ステンシルバッファの作成
    D3D11_TEXTURE2D_DESC texture_desc;
    ZeroMemory(&texture_desc, sizeof(D3D11_TEXTURE2D_DESC));
    // バッファの横幅
    texture_desc.Width = (rect.right - rect.left);
    // バッファの横幅
    texture_desc.Height = (rect.bottom - rect.top);
    // ミップマップレベル
    texture_desc.MipLevels = 1;
    // テクスチャ配列のサイズ
    texture_desc.ArraySize = 1;
    // テクスチャのフォーマット
    // DXGI_FORMAT_D24_UNORM_S8_UINT
    // Depth24bit, Stencil8bitとなる
    texture_desc.Format = DXGI_FORMAT_D32_FLOAT;
    // 
#ifdef ENABLE_MASS
    texture_desc.SampleDesc = m_SampleDesc;
#else
    texture_desc.SampleDesc.Count = 1;
    texture_desc.SampleDesc.Quality = 0;
#endif
    // テクスチャの使用方法
    texture_desc.Usage = D3D11_USAGE_DEFAULT;
    // Bind設定
    // D3D11_BIND_DEPTH_STENCILで問題ない
    texture_desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    // リソースへのCPUのアクセス権限
    // 0で問題ない
    texture_desc.CPUAccessFlags = 0;
    // リソースオプションのフラグ
    // 必要なければ0
    texture_desc.MiscFlags = 0;
    
    // テクスチャの作成
    if (FAILED(m_Device->CreateTexture2D(&texture_desc, NULL, &m_DepthStencilTexture)))
    {
        return false;
    }

    // DepthStencilViewの設定を行う
    D3D11_DEPTH_STENCIL_VIEW_DESC dsv_desc;
    ZeroMemory(&dsv_desc, sizeof(dsv_desc));
    // Viewのフォーマット
    dsv_desc.Format = texture_desc.Format;
    // テクスチャの種類
#ifdef ENABLE_MASS
    dsv_desc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;
#else
    dsv_desc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
#endif
    dsv_desc.Texture2D.MipSlice = 0;
    
    // DepthStencilViewの作成
    if (FAILED(m_Device->CreateDepthStencilView(
        m_DepthStencilTexture,
        &dsv_desc,
        &m_DepthStencilView)))
    {
        return false;
    }

    m_Context->OMSetRenderTargets(1, &m_RenderTargetView, m_DepthStencilView);

    return true;
}

bool DirectGraphics::CreateShader()
{
    m_VertexShader = new VertexShader();
    if (m_VertexShader->Create(m_Device, "Res/Shader/VertexShader.cso") == false)
    {
        return false;
    }

    m_PixelShader = new PixelShader();
    if (m_PixelShader->Create(m_Device, "Res/Shader/PixelShader.cso") == false)
    {
        return false;
    }

    m_SimpleVertexShader = new VertexShader();
    if (m_SimpleVertexShader->Create(m_Device, "Res/Shader/SimpleVertexShader.cso") == false)
    {
        return false;
    }

    m_SimplePixelShader = new PixelShader();
    if (m_SimplePixelShader->Create(m_Device, "Res/Shader/SimplePixelShader.cso") == false)
    {
        return false;
    }

    return true;
}

bool DirectGraphics::CreateConstantBuffer()
{
    D3D11_BUFFER_DESC buffer_desc;
    buffer_desc.ByteWidth           = sizeof(ConstantBuffer);
    buffer_desc.Usage               = D3D11_USAGE_DEFAULT;
    buffer_desc.BindFlags           = D3D11_BIND_CONSTANT_BUFFER;
    buffer_desc.CPUAccessFlags      = 0;
    buffer_desc.MiscFlags           = 0;
    buffer_desc.StructureByteStride = 0;

    if (FAILED(m_Device->CreateBuffer(&buffer_desc, nullptr, &m_ConstantBuffer)))
    {
        return false;
    }
    
    buffer_desc.ByteWidth = sizeof(SimpleConstantBuffer);
    if (FAILED(m_Device->CreateBuffer(&buffer_desc, nullptr, &m_SimpleConstantBuffer)))
    {
        return false;
    }

    buffer_desc.ByteWidth = sizeof(ConstBoneBuffer);
    if (FAILED(m_Device->CreateBuffer(&buffer_desc, nullptr, &m_ConstBoneBuffer)))
    {
        return false;
    }    

    return true;
}

bool DirectGraphics::CreateTextureSampler()
{
    D3D11_SAMPLER_DESC sampler_desc;

    ZeroMemory(&sampler_desc, sizeof(D3D11_SAMPLER_DESC));

    sampler_desc.Filter   = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    sampler_desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    sampler_desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    sampler_desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;


    if (FAILED(m_Device->CreateSamplerState(&sampler_desc, &m_SamplerState)))
    {
        return false;
    }

    sampler_desc.Filter = D3D11_FILTER_COMPARISON_MIN_MAG_MIP_LINEAR;
    sampler_desc.AddressU = D3D11_TEXTURE_ADDRESS_BORDER;
    sampler_desc.AddressV = D3D11_TEXTURE_ADDRESS_BORDER;
    sampler_desc.AddressW = D3D11_TEXTURE_ADDRESS_BORDER;
    sampler_desc.ComparisonFunc = D3D11_COMPARISON_LESS_EQUAL;
    sampler_desc.BorderColor[0] = 1.0f;
    sampler_desc.BorderColor[1] = 1.0f;
    sampler_desc.BorderColor[2] = 1.0f;
    sampler_desc.BorderColor[3] = 1.0f;
    sampler_desc.MaxAnisotropy = 1;
    sampler_desc.MipLODBias = 0;
    sampler_desc.MinLOD = -FLT_MAX;
    sampler_desc.MaxLOD = +FLT_MAX;

    if (FAILED(m_Device->CreateSamplerState(&sampler_desc, &m_ShadowSamplerState)))
    {
        return false;
    }

    return true;
}

void DirectGraphics::SetUpViewPort()
{
    HWND window_handle = FindWindow(Window::ClassName, nullptr);
    RECT rect;
    GetClientRect(window_handle, &rect);

    D3D11_VIEWPORT view_port;
    // 画面左上のX座標
    view_port.TopLeftX = 0;
    // 画面左上のY座標
    view_port.TopLeftY = 0;
    // 横幅
    view_port.Width = (rect.right - rect.left);
    // 縦幅
    view_port.Height = (rect.bottom - rect.top);
    // 深度値の最小値
    view_port.MinDepth = 0.0f;
    // 深度値の最大値
    view_port.MaxDepth = 1.0f;

    // ViewPortの設定
    m_Context->RSSetViewports(1, &view_port);
}