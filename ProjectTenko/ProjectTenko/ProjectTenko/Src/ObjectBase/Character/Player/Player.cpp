#include "Player.h"

Player::Player(D3DXVECTOR3 pos_, std::string key_) :
	Character(pos_, key_)
{
	THE_FBXMANAGER->LoadFBXMesh(key_, "assts/models/player/tenko_sample02.fbx");
}

void Player::Update()
{
}

void Player::Draw()
{
	THE_FBXMANAGER->Draw(m_FbxKey, m_Mat_World);
	THE_FBXMANAGER->Animation(m_FbxKey, 1.0f / 60.0f);
}
