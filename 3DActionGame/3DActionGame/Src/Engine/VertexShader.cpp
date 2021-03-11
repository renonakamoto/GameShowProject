#include "VertexShader.h""

bool VertexShader::Create(ID3D11Device* device_, const char* fileName_)
{
	if (ShaderBase::Create(device_, fileName_) == false)
	{
		return false;
	}


	if (FAILED(device_->CreateVertexShader(m_Data, m_Size, nullptr, &m_Interface)))
	{
		return false;
	}

	return true;
}
