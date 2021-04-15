#ifndef SKELETAL_MODEL_H_
#define SKELETAL_MODEL_H_

#include <string>
#include "../Engine/MeshModel/FbxModel/FbxModel.h"

class SkeletalModel
{
public:
	SkeletalModel() :
		m_Model(nullptr),
		m_PlayMotion(""),
		m_Frame(0.f)
	{}

	~SkeletalModel()
	{}

	void Render(DirectX::XMFLOAT3 pos_, DirectX::XMFLOAT3 scale_, DirectX::XMFLOAT3 degree_);
	
	/**
	* @fn void Play(std::string animName_)
	* @brief 再生するモーションを選択する関数
	* @param[in] animName_ 再生するモーションの名前(モーションを読み込んだ際に設定したキーワード)
	*/
	void Play(std::string animName_);

	/**
	* @fn void Animate(float sec_)
	* @brief モーションを再生する関数
	* @param[in] sec_ 進める時間
	* @details 現在再生中のモーションのフレームを進める、秒数は指定しなくても60/1秒進む
	*/
	void Animate(float sec_ = 1.0f / 60.0f);

	void SetModel(FbxModel* model_) { m_Model = model_; }

	FbxModel* GetModel() { return m_Model; }


	void SetFrame(float frameNum_) { m_Frame = frameNum_; }
	float GetCurrentFrame() { return m_Frame; }
	
private:
	FbxModel*	m_Model;
	std::string m_PlayMotion;	//! 再生されているモーション名
	float		m_Frame;		//! 現在のモーションのフレーム数を保持する変数

};

#endif