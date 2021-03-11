#ifndef VERTEX_SHADER_H_
#define VERTEX_SHADER_H_

#include <d3d11.h>
#include "ShaderBase.h"

class VertexShader : public ShaderBase
{
public:
	VertexShader() :
		m_Interface(nullptr)
	{}

	virtual ~VertexShader()
	{
		if (m_Interface != nullptr)
		{
			m_Interface->Release();
		}
	}

	virtual bool Create(ID3D11Device* device_, const char* fileName_);

	ID3D11VertexShader* GetShaderInterface()
	{
		return m_Interface;
	}

private:
	ID3D11VertexShader* m_Interface;
	
};

#endif