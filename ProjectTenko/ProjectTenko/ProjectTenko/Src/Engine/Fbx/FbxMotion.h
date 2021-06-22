#ifndef FBXMOTION_H_
#define FBXMOTION_H_

#include "FbxManager.h"
#include <string>
#include <map>

/**
* @brief	Fbxのモーション管理クラス
* @tparam T モーションを管理するデータ型
*/
template <class T>
class FbxMotion
{
public:
	/**
	* @brief   コンストラクタ
	* @details クラスの初期化
	*/
	FbxMotion():
		m_CurrentKeyFrame(0)
	{}

	/**
	* @brief   デストラクタ
	*/
	~FbxMotion()
	{
		m_MotioData.clear();
		m_MotionFrameNum.clear();
	}
	
	/**
	* @brief	 モーションを追加する関数
	* @param[in] motionID_	モーションのID
	* @param[in] keyStart_	キーフレームの最初
	* @param[in] keyEnd_	キーフレームの最後
	* @return bool true: 成功 false: 失敗
	*/
	bool AddMotion(T motionID_, int keyStart_, int keyEnd_);

	/**
	* @brief	モーション関数
	* @param[in] motionID_	モーションのID
	* @param[in] fbxKey_	Fbxデータキー
	* @param[in] isLoop_	ループさせるかどうか
	* @param[out] isEnd_	終了したかどうか
	*/
	void Motion(T motionID_, std::string fbxKey_, bool isLoop_ = true, bool* isEnd_ = nullptr);

private:
	using KeyStart = int;
	using KeyEnd   = int;
	
	//! モーションデータ保存変数
	std::map<T, std::pair<KeyStart, KeyEnd>> m_MotioData;
	//! モーションフレーム保存変数
	std::map<T, int> m_MotionFrameNum;
	//! 現在のフレーム数
	int m_CurrentKeyFrame;
	//! 前のモーション情報
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