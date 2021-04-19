#ifndef SKELETAL_MODEL_H_
#define SKELETAL_MODEL_H_

#include <string>
#include "../Engine/Model/FbxModel/FbxModel.h"

/**
* @brief アニメーションを行う動的なモデルを扱うクラス
*/
class SkeletalModel
{
public:
	/**
	* @brief コンストラクタ
	*/
	SkeletalModel() :
		SkeletalModel(nullptr, "")
	{}

	/**
	* @brief コンストラクタ
	*/
	SkeletalModel(FbxModel* model_) :
		SkeletalModel(model_, "")
	{}

	/**
	* @brief コンストラクタ
	*/
	SkeletalModel(FbxModel* model_, std::string motionName_) :
		m_Model(model_),
		m_PlayMotion(motionName_),
		m_Frame(0.f)
	{}

	/**
	* @brief デストラクタ
	*/
	~SkeletalModel()
	{}

	/**
	* @fn void Render(DirectX::XMFLOAT3 pos_, DirectX::XMFLOAT3 scale_, DirectX::XMFLOAT3 degree_)
	* @brief 描画関数
	* @param[in] pos_    座標
	* @param[in] scale_  拡縮
	* @param[in] degree_ 回転
	*/
	void Render(DirectX::XMFLOAT3 pos_, DirectX::XMFLOAT3 scale_, DirectX::XMFLOAT3 degree_);
	
	/**
	* @fn void Play(std::string animName_)
	* @brief 再生するモーションを選択する関数
	* @param[in] animName_ 再生するモーションの名前(モーションを読み込んだ際に設定したキーワード)
	* @details モーションが変わった時にフレームは初期化される
	*/
	void Play(std::string animName_);

	/**
	* @fn void Animate(float sec_)
	* @brief モーションを再生する関数
	* @param[in] sec_ 進める時間
	* @details 現在再生中のモーションのフレームを進める、秒数は指定しなくても60/1秒進む
	*/
	void Animate(float sec_ = 1.0f / 60.0f);

	/**
	* @fn void SetFrame(float frameNum_)
	* @brief モーションのフレームをセットする関数
	* @param[in] frameNum_ セットするモーションのフレーム
	*/
	void SetFrame(float frameNum_) { m_Frame = frameNum_; }

	/**
	* @fn float GetCurrentFrame()
	* @brief 現在のモーションのフレーム数を返す関数
	* @return 現在のモーションのフレーム数
	*/
	float GetCurrentFrame() { return m_Frame; }

	/**
	* @fn void SetModel(FbxModel* model_)
	* @brief 扱うモデルを設定する関数
	* @param[in] model_ モデルデータ
	*/
	void SetModel(FbxModel* model_) { m_Model = model_; }

	/**
	* @fn FbxModel* GetModel()
	* @brief モデルデータの取得関数
	* @return FbxModel* モデルデータのポインタ
	* @details nullptrの可能性もあるので、注意
	*/
	FbxModel* GetModel() { return m_Model; }
	
private:
	FbxModel*	m_Model;		//! Fbxモデル
	std::string m_PlayMotion;	//! 再生されているモーション名
	float		m_Frame;		//! 現在のモーションのフレーム数を保持する変数

};

#endif