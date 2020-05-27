#include "Kabochaten.h"

Kabochaten::Kabochaten(D3DXVECTOR3 pos_, const ObjectBase* player_, std::string key_) :
	Enemybase(pos_, player_, key_)
{
	THE_FBXMANAGER->LoadFBXMesh(key_, "assets/models/enemies/kabochaten/pumpkin_animation.fbx");

	m_Motion.AddMotion(KabochaMotionList::Wait, 0, 60);
	m_Motion.AddMotion(KabochaMotionList::Wait, 70, 130);
	m_Motion.AddMotion(KabochaMotionList::Wait, 140, 200);
	m_Motion.AddMotion(KabochaMotionList::Wait, 210, 270);
	m_Motion.AddMotion(KabochaMotionList::Wait, 280, 340);
}

void Kabochaten::Update()
{
}

void Kabochaten::Draw()
{
	D3DXMATRIX mat_trans;
	D3DXMatrixTranslation(&mat_trans, m_Pos.x, m_Pos.y, m_Pos.z);

	m_Mat_World = mat_trans;
	THE_FBXMANAGER->Draw(m_FbxKey, m_Mat_World);
}
