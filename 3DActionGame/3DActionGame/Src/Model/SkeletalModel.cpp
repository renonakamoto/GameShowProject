#include "SkeletalModel.h"

void SkeletalModel::Render(DirectX::XMFLOAT3 pos_, DirectX::XMFLOAT3 scale_, DirectX::XMFLOAT3 degree_)
{
	m_Model->Render(DirectGraphics::GetInstance(), pos_, scale_, degree_, m_PlayMotion, m_Frame);
}

void SkeletalModel::Play(std::string animName_)
{
	if (m_PlayMotion == animName_) return;
	m_PlayMotion = animName_;
	m_Frame = 0.0f;
}

void SkeletalModel::Animate(float sec_)
{
	const Motion* motion = m_Model->GetMotionData(m_PlayMotion);

	if (!motion) return;

	m_Frame += sec_ * 60.0f;
	if (m_Frame >= motion->FrameNum)
	{
		m_Frame = 0.0f;
	}
}
