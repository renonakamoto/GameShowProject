#include "GraphicsUtility.h"
#include "Calculation.h"

using namespace DirectX;

void CalcTangentAndBinormal(DirectX::XMFLOAT3& p0_, DirectX::XMFLOAT2& uv0_, 
							DirectX::XMFLOAT3& p1_, DirectX::XMFLOAT2& uv1_, 
							DirectX::XMFLOAT3& p2_, DirectX::XMFLOAT2& uv2_, 
							DirectX::XMFLOAT3* outTangent_, DirectX::XMFLOAT3* outBinormal_)
{
	if (outTangent_ == nullptr && outBinormal_ == nullptr) return;

	// 5éüå≥Ç3éüå≥í∏ì_Ç…
	XMFLOAT3 cp0[3] = {
		XMFLOAT3(p0_.x, uv0_.x, uv0_.y),
		XMFLOAT3(p0_.y, uv0_.x, uv0_.y),
		XMFLOAT3(p0_.z, uv0_.x, uv0_.y),
	};
	XMFLOAT3 cp1[3] = {
		XMFLOAT3(p1_.x, uv1_.x, uv1_.y),
		XMFLOAT3(p1_.y, uv1_.x, uv1_.y),
		XMFLOAT3(p1_.z, uv1_.x, uv1_.y),
	};
	XMFLOAT3 cp2[3] = {
		XMFLOAT3(p2_.x, uv2_.x, uv2_.y),
		XMFLOAT3(p2_.y, uv2_.x, uv2_.y),
		XMFLOAT3(p2_.z, uv2_.x, uv2_.y),
	};

	// ïΩñ Ç©ÇÁUVé≤ç¿ïWÇåvéZ
	float u[3], v[3];
	for (int i = 0; i < 3; ++i)
	{
		XMFLOAT3 v1 = Calculation::Sub(cp1[i], cp0[i]);
		XMFLOAT3 v2 = Calculation::Sub(cp2[i], cp1[i]);
		XMFLOAT3 c  = Calculation::Cross(v1, v2);

		u[i] = -c.y / c.x;
		v[i] = -c.z / c.x;
	}

	if (outTangent_) {
		memcpy(outTangent_, u, sizeof(float) * 3);
		*outTangent_ = Calculation::Normalize(*outTangent_);
	}
	if (outBinormal_) {
		memcpy(outBinormal_, v, sizeof(float) * 3);
		*outBinormal_ = Calculation::Normalize(*outBinormal_);
	}

}