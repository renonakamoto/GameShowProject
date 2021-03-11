#ifndef DIRECTGRAPHICS_H_
#define DIRECTGRAPHICS_H_


#include <d3d11.h>

#include "VertexShader.h"
#include "PixelShader.h"
#include "../Utility/GraphicsUtility.h"

class DirectGraphics
{
public:
	static DirectGraphics* GetInstance()
	{
		static DirectGraphics instance;
		return &instance;
	}

	DirectGraphics(){}
	~DirectGraphics(){}

	bool Init();

	void Release();


	void StartRendering();

	void FinishRendering();

	void SetUpContext();

	void SetTexture(ID3D11ShaderResourceView* texture_);	

public:

	ID3D11Device* GetDevice() { return m_Device; }

	ID3D11DeviceContext* GetContext() { return m_Context; }

	VertexShader* GetVertexShader() { return m_VertexShader; }

	ID3D11Buffer* GetConstantBuffer() { return m_ConstantBuffer; }

	ConstantBuffer* GetConstantBufferData() { return &m_ConstantBufferData; }

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
	ID3D11Buffer*			m_ConstantBuffer;		//!
	ConstantBuffer			m_ConstantBufferData;	//!
	ID3D11SamplerState*		m_SamplerState;			//!
	ID3D11SamplerState*		m_ShadowSamplerState;	//!
	DXGI_SAMPLE_DESC		m_SampleDesc;			//!
	
	VertexShader*			m_VertexShader;			//!
	PixelShader*			m_PixelShader;			//!

};

#endif