#include "Tikuwaten.h"

Tikuwaten::Tikuwaten(D3DXVECTOR3 pos_, std::string key_) :
	Enemybase(pos_, key_)
{
	THE_FBXMANAGER->LoadFBXMesh(key_, "assets/models/enemies/tikuwaten/chikuwa_animation.fbx");

	m_Motion.AddMotion(ChikuwaMotionList::Wait,			   0,   60);
	m_Motion.AddMotion(ChikuwaMotionList::Walk,			   70,  130);
	m_Motion.AddMotion(ChikuwaMotionList::Sprint,		   140, 200);
	m_Motion.AddMotion(ChikuwaMotionList::ChangeDirection, 210, 270);
}

void Tikuwaten::Update()
{
}

void Tikuwaten::Draw()
{
	D3DXMATRIX mat_trans;
	D3DXMatrixTranslation(&mat_trans, m_Pos.x, m_Pos.y, m_Pos.z);

	m_Mat_World = mat_trans;
	THE_FBXMANAGER->Draw(m_FbxKey, m_Mat_World);
}
