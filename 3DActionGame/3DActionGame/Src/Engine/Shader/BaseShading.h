#ifndef BASE_SHADING_H_
#define BASE_SHADING_H_

#include "../Graphics/DirectGraphics.h"

class BaseShading
{
public:
	BaseShading()
	{}
	
	~BaseShading()
	{}
	
	bool Init();

	void SetSimpleShading(ID3D11DeviceContext* context_, ID3D11ShaderResourceView* srv_);

	void SetPhongShading(ID3D11DeviceContext* context_);
	
private:
	ComPtr<ID3D11InputLayout>     m_InputLayout;
	std::unique_ptr<VertexShader> m_VertexShader;			
	std::unique_ptr<PixelShader>  m_PixelShader;
	ComPtr<ID3D11ClassLinkage>    m_PSClassLinkage;
	ComPtr<ID3D11ClassInstance>   m_ClassInstance;
};

#endif