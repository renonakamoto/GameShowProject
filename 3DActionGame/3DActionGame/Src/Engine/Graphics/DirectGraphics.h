#ifndef DIRECTGRAPHICS_H_
#define DIRECTGRAPHICS_H_

#include <d3d11.h>
#include "VertexShader.h"
#include "PixelShader.h"
#include "../../Utility/GraphicsUtility.h"

/**
* @brief DirectXのグラフィック関連を扱うクラス
*/
class DirectGraphics
{
public:
	/**
	* @brief コンストラクタ
	*/
	DirectGraphics() :
#pragma region MemberInit
		m_Device(nullptr),
		m_Context(nullptr),
		m_SwapChain(nullptr),
		m_RenderTargetView(nullptr),
		m_DepthStencilTexture(nullptr),
		m_DepthStencilView(nullptr),
		m_ConstantBuffer(nullptr),
		m_ConstantBufferData(),
		m_ConstBoneBuffer(nullptr),
		m_ConstBoneBufferData(),
		m_VertexShader(nullptr),
		m_PixelShader(nullptr),
		m_SimpleVertexShader(nullptr),
		m_SimplePixelShader(nullptr),
		m_ShadowSamplerState(nullptr),
		m_FeatureLevel(D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_10_0),
		m_SamplerState(nullptr),
		m_SampleDesc{ 0 }
#pragma endregion
	{}

	/**
	* @brief デストラクタ
	*/
	~DirectGraphics()
	{}

	/**
	* @fn bool Init()
	* @brief 初期化関数
	* @return bool 成功したかどうかを真偽で返す
	* @details DirectX関連の初期化を行う
	*/
	bool Init();

	/**
	* @fn void Release()
	* @brief 解放関数
	* @details ゲーム終了時に行う
	*/
	void Release();
	
	/**
	* @fn void StartRendering()
	* @brief 描画開始関数
	* @details バックバッファの情報をクリアする
	*/
	void StartRendering();

	/**
	* @fn void FinishRendering()
	* @brief 描画終了関数
	* @details バックバッファの情報をフロントバッファに送る
	*/
	void FinishRendering();

public:

	ID3D11Device* GetDevice() { return m_Device; }
	ID3D11DeviceContext* GetContext() { return m_Context; }

	VertexShader* GetVertexShader()	{ return m_VertexShader; }
	PixelShader* GetPixelShader() { return m_PixelShader; }
	VertexShader* GetSimpleVertexShader() { return m_SimpleVertexShader; }
	PixelShader* GetSimplePixelShader() { return m_SimplePixelShader; }

	ID3D11Buffer* GetConstantBuffer()  { return m_ConstantBuffer; }
	ConstantBuffer* GetConstantBufferData(){ return &m_ConstantBufferData; }

	ID3D11Buffer* GetConstBoneBuffer() { return m_ConstBoneBuffer; }
	ConstBoneBuffer* GetConstBoneBufferData() { return &m_ConstBoneBufferData; }

	/**
	* @fn void SetTexture(ID3D11ShaderResourceView* texture_)
	* @brief テクスチャをピクセルシェーダに送る関数
	* @param[in] texture_ テクスチャデータ
	* @details 設定しないときはnullptr
	*/
	void SetTexture(ID3D11ShaderResourceView* texture_);

	/**
	* @fn void SetMaterial(ObjMaterial* material_)
	* @brief マテリアルを定数バッファにセットする関数
	* @param[in] material_ マテリアルデータ
	* @details 設定しないときはnullptr
	*/
	void SetMaterial(ObjMaterial* material_);

private:
	
	void SetUpDxgiSwapChanDesc(DXGI_SWAP_CHAIN_DESC* dxgi);

	bool CreateDeviceAndSwapChain();

	bool CreateRenderTargetView();

	bool CreateDepthAndStencilView();

	bool CreateShader();

	bool CreateConstantBuffer();

	bool CreateTextureSampler();

	void SetUpViewPort();

private:
	ID3D11Device*			m_Device;				//! デバイス
	ID3D11DeviceContext*	m_Context;				//! コンテキスト
	D3D_FEATURE_LEVEL 		m_FeatureLevel;			//! フューチャーレベル
	IDXGISwapChain*			m_SwapChain;			//! スワップチェイン
	ID3D11RenderTargetView* m_RenderTargetView;		//! レンダーターゲットビュー
	ID3D11Texture2D*		m_DepthStencilTexture;	//! 
	ID3D11DepthStencilView* m_DepthStencilView;		//!
	ID3D11SamplerState*		m_SamplerState;			//!
	DXGI_SAMPLE_DESC		m_SampleDesc;			//!
	
	ID3D11Buffer*			m_ConstantBuffer;		//! モデル用のコンストバッファ
	ConstantBuffer			m_ConstantBufferData;	//!	モデル用のコンストバッファ

	ID3D11Buffer*			m_ConstBoneBuffer;		//! ボーン用のコンストバッファ
	ConstBoneBuffer			m_ConstBoneBufferData;	//! ボーン用のコンストバッファ
	
	VertexShader*			m_VertexShader;			//! スキンメッシュ用の頂点シェーダ
	PixelShader*			m_PixelShader;			//! スキンメッシュ用のピクセルシェーダ

	VertexShader*			m_SimpleVertexShader;	//!	スタティックメッシュ用の頂点シェーダ
	PixelShader*			m_SimplePixelShader;	//! スタティックメッシュ用のぷくセルシェーダ

	ID3D11SamplerState* m_ShadowSamplerState;	//!
};

#endif