#include "Engine.h"

bool Engine::Init(int windowWidth_, int windowHeight_, const char* titleName_, HINSTANCE hInstance_)
{
	// Windowの作成
	if (m_Window.Create(windowWidth_, windowHeight_, titleName_) == false)
	{
		return false;
	}

	// Graphicsの作成
	if (m_Graphics.Init() == false)
	{
		return false;
	}

	// Inputの作成
	if (m_Input.Init(hInstance_, m_Window.GetWindowHandle()) == false)
	{
		return false;
	}

	// Soundの作成
	if (m_Sound.Init(m_Window.GetWindowHandle()) == false)
	{
		return false;
	}

	// Textureの作成
	if (m_Texture.Init(m_Graphics.GetDevice()) == false)
	{
		return false;
	}

	// Engineの作成成功
	return true;
}

void Engine::Release()
{
	m_Graphics.Release();
	m_Input.Release();
	m_Sound.Release();
	m_Texture.AllRelease();
}