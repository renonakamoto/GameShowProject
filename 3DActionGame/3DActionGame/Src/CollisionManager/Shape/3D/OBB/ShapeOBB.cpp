#include "ShapeOBB.h"
#include "../../../../Utility/Calculation.h"
#include "../../../../Engine/Engine.h"

bool ShapeOBB::HitTest(Shape3D& shape_)
{
	return shape_.HitTest(*this);
}

bool ShapeOBB::HitTest(ShapeOBB& shape_)
{
	DirectX::XMFLOAT3 nae1 = m_NormalDirect[0], ae1 = Calculation::Mul(nae1, m_Length[0]);
	DirectX::XMFLOAT3 nae2 = m_NormalDirect[1], ae2 = Calculation::Mul(nae2, m_Length[1]);
	DirectX::XMFLOAT3 nae3 = m_NormalDirect[2], ae3 = Calculation::Mul(nae3, m_Length[2]);
	DirectX::XMFLOAT3 nbe1 = shape_.m_NormalDirect[0], be1 = Calculation::Mul(nbe1, shape_.m_Length[0]);
	DirectX::XMFLOAT3 nbe2 = shape_.m_NormalDirect[1], be2 = Calculation::Mul(nbe2, shape_.m_Length[1]);
	DirectX::XMFLOAT3 nbe3 = shape_.m_NormalDirect[2], be3 = Calculation::Mul(nbe3, shape_.m_Length[2]);
	DirectX::XMFLOAT3 interval = Calculation::Sub(m_Pos, shape_.m_Pos);

	// 分離軸 a1
	float r_a = Calculation::Length(ae1);
	float r_b = LenSegOnSeparateAxis(nae1, be1, be2, &be3);
	float l = fabsf(Calculation::Dot(interval, nae1));
	if (l > r_a + r_b) {
		return false;
	}

	// 分離軸 a2
	r_a = Calculation::Length(ae2);
	r_b = LenSegOnSeparateAxis(nae2, be1, be2, &be3);
	l = fabsf(Calculation::Dot(interval, nae2));
	if (l > r_a + r_b) {
		return false;
	}
	
	// 分離軸 a3
	r_a = Calculation::Length(ae3);
	r_b = LenSegOnSeparateAxis(nae3, be1, be2, &be3);
	l = fabsf(Calculation::Dot(interval, nae3));
	if (l > r_a + r_b) {
		return false;
	}


	// 分離軸 b1
	r_a = Calculation::Length(be1);
	r_b = LenSegOnSeparateAxis(nbe1, ae1, ae2, &ae3);
	l = fabsf(Calculation::Dot(interval, nbe1));
	if (l > r_a + r_b) {
		return false;
	}

	// 分離軸 b2
	r_a = Calculation::Length(be2);
	r_b = LenSegOnSeparateAxis(nbe2, ae1, ae2, &ae3);
	l = fabsf(Calculation::Dot(interval, nbe2));
	if (l > r_a + r_b) {
		return false;
	}

	// 分離軸 b3
	r_a = Calculation::Length(be3);
	r_b = LenSegOnSeparateAxis(nbe3, ae1, ae2, &ae3);
	l = fabsf(Calculation::Dot(interval, nbe3));
	if (l > r_a + r_b) {
		return false;
	}


	// 分離軸c11
	DirectX::XMFLOAT3 cross = Calculation::Cross(nae1, nbe1);
	r_a = LenSegOnSeparateAxis(cross, ae2, ae3);
	r_b = LenSegOnSeparateAxis(cross, be2, be3);
	l = fabsf(Calculation::Dot(interval, cross));
	if (l > r_a + r_b) {
		return false;
	}
	
	// 分離軸c12
	cross = Calculation::Cross(nae1, nbe2);
	r_a = LenSegOnSeparateAxis(cross, ae2, ae3);
	r_b = LenSegOnSeparateAxis(cross, be1, be3);
	l = fabsf(Calculation::Dot(interval, cross));
	if (l > r_a + r_b) {
		return false;
	}

	// 分離軸c13
	cross = Calculation::Cross(nae1, nbe3);
	r_a = LenSegOnSeparateAxis(cross, ae2, ae3);
	r_b = LenSegOnSeparateAxis(cross, be1, be2);
	l = fabsf(Calculation::Dot(interval, cross));
	if (l > r_a + r_b) {
		return false;
	}
	
	// 分離軸c21
	cross = Calculation::Cross(nae2, nbe1);
	r_a = LenSegOnSeparateAxis(cross, ae1, ae3);
	r_b = LenSegOnSeparateAxis(cross, be2, be3);
	l = fabsf(Calculation::Dot(interval, cross));
	if (l > r_a + r_b) {
		return false;
	}

	// 分離軸c22
	cross = Calculation::Cross(nae2, nbe2);
	r_a = LenSegOnSeparateAxis(cross, ae1, ae3);
	r_b = LenSegOnSeparateAxis(cross, be1, be3);
	l = fabsf(Calculation::Dot(interval, cross));
	if (l > r_a + r_b) {
		return false;
	}

	// 分離軸c23
	cross = Calculation::Cross(nae2, nbe3);
	r_a = LenSegOnSeparateAxis(cross, ae1, ae3);
	r_b = LenSegOnSeparateAxis(cross, be1, be2);
	l = fabsf(Calculation::Dot(interval, cross));
	if (l > r_a + r_b) {
		return false;
	}

	// 分離軸c31
	cross = Calculation::Cross(nae3, nbe1);
	r_a = LenSegOnSeparateAxis(cross, ae1, ae2);
	r_b = LenSegOnSeparateAxis(cross, be2, be3);
	l = fabsf(Calculation::Dot(interval, cross));
	if (l > r_a + r_b) {
		return false;
	}

	// 分離軸c32
	cross = Calculation::Cross(nae3, nbe2);
	r_a = LenSegOnSeparateAxis(cross, ae1, ae2);
	r_b = LenSegOnSeparateAxis(cross, be1, be3);
	l = fabsf(Calculation::Dot(interval, cross));
	if (l > r_a + r_b) {
		return false;
	}

	// 分離軸c33
	cross = Calculation::Cross(nae3, nbe3);
	r_a = LenSegOnSeparateAxis(cross, ae1, ae2);
	r_b = LenSegOnSeparateAxis(cross, be1, be2);
	l = fabsf(Calculation::Dot(interval, cross));
	if (l > r_a + r_b) {
		return false;
	}

	// 分離平面が存在しないので衝突している
	return true;
}

float ShapeOBB::LenSegOnSeparateAxis(DirectX::XMFLOAT3& spe_, DirectX::XMFLOAT3& e1_, DirectX::XMFLOAT3& e2_, DirectX::XMFLOAT3* e3_)
{
	float r1 = fabsf(Calculation::Dot(spe_, e1_));
	float r2 = fabsf(Calculation::Dot(spe_, e2_));
	float r3 = e3_ ? (fabsf(Calculation::Dot(spe_, *e3_))) : 0.f;

	return r1 + r2 + r3;
}

void ShapeOBB::Draw()
{
	DirectGraphics* graphics = GRAPHICS;
	ID3D11DeviceContext* context = GRAPHICS->GetContext();

	// ラスタラスザの設定
	graphics->SetRasterizerMode(RasterizerMode::MODE_WIREFRAME);
	// 頂点シェーダの設定
	context->VSSetShader(graphics->GetSimpleVertexShader()->GetShaderInterface(), NULL, 0U);
	// ピクセルシェーダの設定
	context->PSSetShader(graphics->GetPixelShader()->GetShaderInterface(), NULL, 0U);
	
	DirectX::XMFLOAT3 pos   = m_Pos;
	DirectX::XMFLOAT3 scale = DirectX::XMFLOAT3(m_Length[0], m_Length[1], m_Length[2]);
	float y = atan2f(m_NormalDirect[2].x, m_NormalDirect[2].z);
	DirectX::XMFLOAT3 rot = DirectX::XMFLOAT3(0.f, DirectX::XMConvertToDegrees(y), 0.f);

	m_OBB->Render(pos, scale, rot);
}
