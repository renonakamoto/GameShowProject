#include "DirectGraphics.h"

bool MyDirectGraphics::DirectGraphics::Init(HWND windowHandle_, int width_, int height_, bool isFullScreen_)
{
	if (CreateGraphicsInterface() == false) { return false; }
	if (CreateGraphicsDevice(windowHandle_, width_, height_, isFullScreen_) == false) { return false; }
	if (SetViewPort() == false) { return false; }

	m_pD3DDevice->SetRenderState(D3DRS_SPECULARENABLE, true);

	return true;
}

void MyDirectGraphics::DirectGraphics::StartDraw()
{
	m_pD3DDevice->Clear(0, NULL,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(0, 0, 255),
		1.0f,
		0);
	
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	m_pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);

	m_pD3DDevice->BeginScene();
}

void MyDirectGraphics::DirectGraphics::EndDraw()
{
	m_pD3DDevice->EndScene();
	m_pD3DDevice->Present(nullptr, nullptr, nullptr, nullptr);
}

bool MyDirectGraphics::DirectGraphics::CreateGraphicsInterface()
{
	//! インターフェース取得
	m_pD3DInterface = Direct3DCreate9(D3D_SDK_VERSION);
	if (m_pD3DInterface == nullptr)
	{
		//! 取得に失敗
		return false;
	}

	//! 取得に成功
	return true;
}

bool MyDirectGraphics::DirectGraphics::CreateGraphicsDevice(HWND windowHandle_, int width_, int height_, bool isFullScreen_)
{
	m_pD3DPresentParam = new D3DPRESENT_PARAMETERS;
	if (m_pD3DPresentParam == nullptr)
	{
		return false;
	}
	ZeroMemory(m_pD3DPresentParam, sizeof(D3DPRESENT_PARAMETERS));

	m_pD3DPresentParam->Windowed			= !isFullScreen_;
	m_pD3DPresentParam->hDeviceWindow		= windowHandle_;
	m_pD3DPresentParam->BackBufferCount		= 1;
	m_pD3DPresentParam->BackBufferFormat	= D3DFMT_A8R8G8B8;
	m_pD3DPresentParam->SwapEffect			= D3DSWAPEFFECT_DISCARD;
	m_pD3DPresentParam->MultiSampleType		= D3DMULTISAMPLE_NONE;
	m_pD3DPresentParam->MultiSampleQuality	= 0;
	m_pD3DPresentParam->AutoDepthStencilFormat = D3DFMT_D24S8;
	m_pD3DPresentParam->EnableAutoDepthStencil = true;
	m_pD3DPresentParam->BackBufferWidth		= width_;
	m_pD3DPresentParam->BackBufferHeight	= height_;


	if (isFullScreen_)
	{
		m_pD3DPresentParam->FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	}

	if (FAILED(m_pD3DInterface->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		m_pD3DPresentParam->hDeviceWindow,
		D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED,
		m_pD3DPresentParam,
		&m_pD3DDevice)))
	{
		m_pD3DInterface->Release();
		m_pD3DInterface = nullptr;
		return false;
	}

	return true;
}

bool MyDirectGraphics::DirectGraphics::SetViewPort()
{
	D3DVIEWPORT9 viewPort;

	viewPort.X = 0;
	viewPort.Y = 0;
	viewPort.Width  = m_pD3DPresentParam->BackBufferWidth;
	viewPort.Height = m_pD3DPresentParam->BackBufferHeight;
	viewPort.MinZ = 0.0f;
	viewPort.MaxZ = 1.0f;

	if (FAILED(m_pD3DDevice->SetViewport(&viewPort)))
	{
		//! ビューポートの設定に失敗
		return false;
	}

	//! ビューポートの設定に成功
	return true;
}
