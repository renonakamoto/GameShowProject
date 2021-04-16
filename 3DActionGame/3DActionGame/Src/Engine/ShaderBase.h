#ifndef SHADER_BASE_H_
#define SHADER_BASE_H_

#include <d3d11.h>


class ShaderBase
{
public:
	ShaderBase():
		m_Data(nullptr),
		m_Size(0)
	{}

	~ShaderBase(){}

	inline const char* GetData()
	{
		return m_Data;
	}

	inline long GetSize()
	{
		return m_Size;
	}

	virtual bool Create(ID3D11Device* device_, const char* fileName_);

private:
	int LoadFile(const char* fileName_);

protected:
	union ShaderInterface
	{
		ID3D11VertexShader* Vertex;
		ID3D11PixelShader*  Pixel;
	};

	char* m_Data;
	long  m_Size;
};

#endif