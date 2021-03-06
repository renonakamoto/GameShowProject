#include "FbxManager.h"

MyFbx::FbxManager::FbxManager()
{
	m_FbxLoader = std::make_unique<FbxLoader>();
	m_FbxDrawe  = std::make_unique<FbxDrawer>();
}

MyFbx::FbxManager::~FbxManager()
{
}

bool MyFbx::FbxManager::LoadFBXMesh(std::string key_, const char* pFileName_)
{
	//! キーが存在する場合
	if (HasKey(key_) == true) { return false; }

	m_ObjectMeshData[key_] = m_FbxLoader->LoadFBXMesh(pFileName_);
	return true;
}

void MyFbx::FbxManager::ReleaseFbxMesh(std::string key_)
{
	if (HasKey(key_) == false) { return; }

	m_FbxLoader.get()->ReleaseFbxMesh(m_ObjectMeshData[key_]);
	m_ObjectMeshData.erase(key_);
}

void MyFbx::FbxManager::AllReleaseFbxMesh()
{
	for (auto& mesh_data : m_ObjectMeshData)
	{
		m_FbxLoader.get()->ReleaseFbxMesh(mesh_data.second);

	}

	m_ObjectMeshData.clear();
}

void MyFbx::FbxManager::Draw(std::string key_, const D3DXMATRIX& world_, UCHAR alpha_)
{
	if (HasKey(key_) == false) { return; }

	m_ObjectMeshData[key_]->Model.world = world_;

	m_FbxDrawe->RenderFbxMesh(m_ObjectMeshData[key_], alpha_);
}

void MyFbx::FbxManager::Animation(std::string key_, float sec_)
{
	if (HasKey(key_) == false) { return; }

	m_FbxDrawe->Animate(m_ObjectMeshData[key_], sec_);
}

void MyFbx::FbxManager::ResetAnimation(std::string key_)
{
	if (HasKey(key_) == false) { return; }

	m_FbxDrawe->ResetAnimate(m_ObjectMeshData[key_]);
}

bool MyFbx::FbxManager::HasKey(std::string key_)
{
	auto itr = m_ObjectMeshData.find(key_);
	if (itr != m_ObjectMeshData.end())
	{
		return true;
	}

	return false;
}