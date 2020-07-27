#ifndef MAPDATABANK_H_
#define MAPDATABANK_H_

#include <string>
#include <vector>

class MapObjectData;

namespace MapData
{
	/**
	* @brief   �}�b�v�I�u�W�F�N�g�̎��
	*/
	enum class MapObjectList
	{
		Barrel,				//! �M
		Floor,				//! ��
		Gate,				//! �Q�[�g
		Merrygoland,		//! �����[�S�[�����h
		Mountain,			//! �R
		Skydome,			//!	�X�J�C�h�[��
		Tent,				//!	�e���g
		Vending_Machine,	//!	���̋@
		Wall,				//!	��
		Tree,				//!	��
		Sapling_Small,		//!	�c��(��)
		Sapling_Big,		//! �c��(��)
		Ferris_Wheel,		//!	�ϗ���
		Shrimp_Statue,		//!	�C�V�V�̑�

		MaxMapObject,		//! ��ނ̐�
	};

	/**
	* @brief   �}�b�v�I�u�W�F�N�g�̃f�[�^���X�g
	*/
	enum class MapObjectDataList
	{
		ObjectName,	//! �I�u�W�F�N�g�̖��O

		PosX,		//! X���W
		PosY,		//! Y���W
		PosZ,		//! Z���W

		ScalX,		//! X�X�P�[��
		ScalY,		//!	Y�X�P�[��
		ScalZ,		//!	Z�X�P�[��

		RotX,		//!	X����]
		RotY,		//!	Y����]
		RotZ,		//!	Z����]
	};
}

/**
* @brief   �}�b�v�I�u�W�F�N�g�̃f�[�^�������N���X
* @details �}�b�v�I�u�W�F�N�g�̃f�[�^��CSV����ǂݍ��ݕϊ�����
*/
class MapDataBank
{
public:
	/**
	* @brief Csv����}�b�v�f�[�^��ǂݍ���
	* @return bool ����:true ���s:false
	*/
	bool Load();

	/**
	* @brief �}�b�v�̃f�[�^��Ԃ��֐�
	* @param[in] objectId_ �I�u�W�F�N�g�̎��
	* @return std::vector<MapObjectData>* �}�b�v�I�u�W�F�N�g�f�[�^
	*/
	std::vector<MapObjectData>* GetMapObjectData(MapData::MapObjectList objectId_)
	{
		return &m_MapObjectDataList[static_cast<int>(objectId_)];
	}

private:
	//!	�O������ǂݍ��񂾃}�b�v�I�u�W�F�N�g�̃f�[�^��ۑ�����ϐ�
	std::vector<MapObjectData> m_MapObjectDataList[static_cast<int>(MapData::MapObjectList::MaxMapObject)];

};

#endif