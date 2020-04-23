#ifndef FBXMOTION_H_
#define FBXMOTION_H_

#include "FbxManager.h"
#include <string>
#include <map>

template <class T>
class FbxMotion
{
public:
	FbxMotion():
		m_CurrentKeyFrame(0)
	{}

	~FbxMotion()
	{
		m_MotionList.clear();
		m_MotionFrameNum.clear();
	}
	
	bool AddMotion(T motionID_, int keyStart_, int keyEnd_);

	void Motion(T motionID_, std::string fbxKey_, bool isLoop_ = true, bool* isEnd_ = nullptr);

private:
	typedef int KeyStart;
	typedef int KeyEnd;

	std::map<T, std::pair<KeyStart, KeyEnd>> m_MotionList;
	std::map<T, int> m_MotionFrameNum;
	int m_CurrentKeyFrame;

	T m_BeforMotion;
};

#endif

template<class T>
inline bool FbxMotion<T>::AddMotion(T motionID_, int keyStart_, int keyEnd_)
{
	if (m_MotionList.find(motionID_) != m_MotionList.end()) return false;

	m_MotionList[motionID_] = std::make_pair(keyStart_, keyEnd_);
	m_MotionFrameNum[motionID_] = keyEnd_ - keyStart_;

	return true;
}

template<class T>
inline void FbxMotion<T>::Motion(T motionID_, std::string fbxKey_, bool isLoop_, bool* isEnd_)
{
	if (m_MotionList.find(motionID_) == m_MotionList.end()) return;

	if (m_BeforMotion != motionID_)
	{
		m_CurrentKeyFrame = 0;
		m_BeforMotion	  = motionID_;
	}

	THE_FBXMANAGER->Animation(fbxKey_, m_MotionList[motionID_].first + m_CurrentKeyFrame);

	m_CurrentKeyFrame++;

	if (m_CurrentKeyFrame > m_MotionFrameNum[motionID_])
	{
		isLoop_ ? m_CurrentKeyFrame = 0 : m_CurrentKeyFrame = m_MotionFrameNum[motionID_];
		if (isEnd_)* isEnd_ = true;
	}
}