#ifndef PIXELSHADER_H_
#define PIXELSHADER_H_

#include <d3d11.h>
#include "ShaderBase.h"

class PixelShader : public ShaderBase
{
public:
	PixelShader():
		m_Interface(nullptr)
	{}

	virtual ~PixelShader()
	{
		if (m_Interface != nullptr)
		{
			m_Interface->Release();
		}
	}

	virtual bool Create(ID3D11Device* device_, const char* fileName_);

	ID3D11PixelShader* GetShaderInterface()
	{
		return m_Interface;
	}

private:
	ID3D11PixelShader* m_Interface;
};

#endif