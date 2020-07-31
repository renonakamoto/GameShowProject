#ifndef MAPOBJECT_H_
#define MAPOBJECT_H_

#include "../ObjectBase.h"
#include "../MapObject/MapDataBank.h"
#include <vector>


struct MapObjectData
{
	/**
	* @brief	�R���X�g���N�^
	*/
	MapObjectData() :
		m_Pos(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
		m_Scale(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
		m_Rot(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
	{}

	/**
	* @brief	�����t���R���X�g���N�^
	*/
	MapObjectData(D3DXVECTOR3 pos_, D3DXVECTOR3 scale_, D3DXVECTOR3 rot_, float width_, float height_, float depth_):
		m_Pos(pos_),
		m_Scale(scale_),
		m_Rot(rot_)
	{}

	D3DXVECTOR3 m_Pos;		//! ���W
	D3DXVECTOR3 m_Scale;	//! �X�P�[��
	D3DXVECTOR3 m_Rot;		//! ��]

};

class MapObject : public ObjectBase
{
public:
	/**
	* @brief �����t���R���X�g���N�^
	*/
	template<typename... KeyList>
	MapObject(std::vector<MapObjectData>* mapObjcectList_, const KeyList&... keyList) :
		m_MapObjectDataList(mapObjcectList_)
	{
		Develop(keyList...);
	}

	/**
	* @brief �f�X�g���N�^
	*/
	virtual ~MapObject() {}

	// �ēǂݍ���
	void CoordinateUpdate(MapData::MapObjectList mapObjId_)
	{
		//TODO MapDataBank���V���O���g��
		MapDataBank hoge;
		hoge.Load();
		m_MapObjectDataList = hoge.GetMapObjectData(mapObjId_);
	}

protected:
	std::vector<MapObjectData>* m_MapObjectDataList;
	//! ���[���h�s��
	std::vector<D3DXMATRIX> m_MatWorld;
	//! Fbx�f�[�^�̃L�[
	std::vector<std::string> m_FbxKeys;
		 

private:
	template<typename First, typename... Rest>
	void Develop(const First& first_, const Rest&... rest_)
	{
		m_FbxKeys.push_back(first_);
		Develop(rest_...);
	}

	//! �������[�v�ɂȂ�Ȃ��悤��
	void Develop() { return; }

};

#endif