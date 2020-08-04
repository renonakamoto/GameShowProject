#include "FerrisWheel.h"

void FerrisWheel::Update()
{
#ifdef MAP_DEBUG
	CoordinateUpdate(MapData::MapObjectList::Ferris_Wheel);
#endif

	D3DXMATRIX mat_rot_z;

	// Y����]���s��
	D3DXMatrixRotationZ(&mat_rot_z, D3DXToRadian(m_Angle));

	// Y����]�s��������̃��[���h�s���Y����]�����ɑ������
	for (auto& v : m_WorldRotatingParts)
	{
		v._11 = mat_rot_z._11;
		v._12 = mat_rot_z._12;
		v._21 = mat_rot_z._21;
		v._22 = mat_rot_z._22;
	}

	m_Angle++;
	if (m_Angle > 360.0f)
	{
		m_Angle = 0;
	}
}

void FerrisWheel::Draw()
{
	for (const auto& mat_world : m_MatWorld)
	{
		THE_FBXMANAGER->Draw(m_FbxKeys[static_cast<int>(FerrisWheelParts::FerrisWheel_Foundation)], mat_world);
	}

	for (const auto& mat_world : m_WorldRotatingParts)
	{
		THE_FBXMANAGER->Draw(m_FbxKeys[static_cast<int>(FerrisWheelParts::FerrisWheel_Rotating)], mat_world);
	}
}
