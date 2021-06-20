#include "PixelShader.h"

bool PixelShader::Create(ID3D11Device* device_, const char* fileName_)
{
	if (ShaderBase::Create(device_, fileName_) == false)
	{
		return false;
	}

	if (FAILED(device_->CreatePixelShader(m_Data, m_Size, nullptr, m_Interface.GetAddressOf())))
	{
		return false;
	}

	return true;
}

bool PixelShader::Create(ID3D11Device* device_, const char* fileName_, ID3D11ClassLinkage* classLinkage_)
{
	if (ShaderBase::Create(device_, fileName_) == false)
	{
		return false;
	}

	if (FAILED(device_->CreatePixelShader(m_Data, m_Size, classLinkage_, m_Interface.GetAddressOf())))
	{
		return false;
	}

	return false;
}
