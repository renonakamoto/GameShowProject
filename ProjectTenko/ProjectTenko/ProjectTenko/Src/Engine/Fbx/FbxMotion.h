#ifndef FBXMOTION_H_
#define FBXMOTION_H_

#include "FbxManager.h"
#include <string>
#include <map>

/**
* @brief	Fbx�̃��[�V�����Ǘ��N���X
* @tparam T ���[�V�������Ǘ�����f�[�^�^
*/
template <class T>
class FbxMotion
{
public:
	/**
	* @brief   �R���X�g���N�^
	* @details �N���X�̏�����
	*/
	FbxMotion():
		m_CurrentKeyFrame(0)
	{}

	/**
	* @brief   �f�X�g���N�^
	*/
	~FbxMotion()
	{
		m_MotioData.clear();
		m_MotionFrameNum.clear();
	}
	
	/**
	* @brief	 ���[�V������ǉ�����֐�
	* @param[in] motionID_	���[�V������ID
	* @param[in] keyStart_	�L�[�t���[���̍ŏ�
	* @param[in] keyEnd_	�L�[�t���[���̍Ō�
	* @return bool true: ���� false: ���s
	*/
	bool AddMotion(T motionID_, int keyStart_, int keyEnd_);

	/**
	* @brief	���[�V�����֐�
	* @param[in] motionID_	���[�V������ID
	* @param[in] fbxKey_	Fbx�f�[�^�L�[
	* @param[in] isLoop_	���[�v�����邩�ǂ���
	* @param[out] isEnd_	�I���������ǂ���
	*/
	void Motion(T motionID_, std::string fbxKey_, bool isLoop_ = true, bool* isEnd_ = nullptr);

private:
	using KeyStart = int;
	using KeyEnd   = int;
	
	//! ���[�V�����f�[�^�ۑ��ϐ�
	std::map<T, std::pair<KeyStart, KeyEnd>> m_MotioData;
	//! ���[�V�����t���[���ۑ��ϐ�
	std::map<T, int> m_MotionFrameNum;
	//! ���݂̃t���[����
	int m_CurrentKeyFrame;
	//! �O�̃��[�V�������
	T m_OldMotion;
};

#endif

template<class T>
inline bool FbxMotion<T>::AddMotion(T motionID_, int keyStart_, int keyEnd_)
{
	if (m_MotioData.find(motionID_) != m_MotioData.end()) return false;

	m_MotioData[motionID_] = std::make_pair(keyStart_, keyEnd_);
	m_MotionFrameNum[motionID_] = keyEnd_ - keyStart_;

	return true;
}

template<class T>
inline void FbxMotion<T>::Motion(T motionID_, std::string fbxKey_, bool isLoop_, bool* isEnd_)
{
	if (m_MotioData.find(motionID_) == m_MotioData.end()) return;

	if (m_OldMotion != motionID_)
	{
		m_CurrentKeyFrame = 0;
		m_OldMotion = motionID_;
	}

	THE_FBXMANAGER->Animation(fbxKey_, m_MotioData[motionID_].first + m_CurrentKeyFrame);

	m_CurrentKeyFrame++;

	if (m_CurrentKeyFrame > m_MotionFrameNum[motionID_])
	{
		isLoop_ ? m_CurrentKeyFrame = 0 : m_CurrentKeyFrame = m_MotionFrameNum[motionID_];
		if (isEnd_) *isEnd_ = true;
	}
}