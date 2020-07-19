#ifndef PLAYER_H_
#define PLAYER_H_

#include "../../../Camera/Camera.h"
#include "../Character.h"
#include "PlayerEffect.h"
#include "State/PlayerStateBase.h"
#include <memory>

/**
* @brief   プレイヤークラス
*/
class Player : public Character
{
public:
	/**
	* @brief コンストラクタ
	*/
	Player(D3DXVECTOR3 pos_, std::string key_);

	/**
	* @brief デストラクタ
	*/
	virtual ~Player();

	/**
	* @brief 更新関数
	*/
	virtual void Update() override;

	/**
	* @brief 描画関数
	*/
	virtual void Draw()   override;

	/**
	* @brief		
	* @return bool	true: 動いている false: 動いていない
	*/
	bool IsMove() { return m_IsMove; }

	/**
	* @brief		モーション関数
	* @details		PlayerStateで使う
	* @param[in]	motionId_	モーションID
	* @param[in]	isLoop_		true: ループさせる false: ループさせない
	* @param[in]	*isEnd_		true: しゃがんでいる false: しゃがんでいない
	*/
	void Motion(PlayerMotionList motionId_, bool isLoop_ = true, bool* isEnd_ = nullptr);

	/**
	* @brief			状態遷移関数
	* @details			PlayerStateで使う
	* @param[in] state_	遷移したい状態
	*/
	void ChangeState(PlayerStateBase* state_);

	/**
	* @brief		セッター
	* @details		PlayerStateで使う
	* @param[in]	isSquad_	 true: しゃがんでいる false: しゃがんでいない
	*/
	void SetIsSquad(bool isSquad_) { m_IsSquat = isSquad_; }

private:
	/**
	* @brief 移動処理
	*/
	void Move();
	

	Camera* m_RefCamera;					//! カメラの参照用変数

	float m_WalkSpeed;						//! 立ってる状態でのスピード
	float m_SquatWalkSpeed;					//! しゃがんでる状態でのスピード

	bool m_IsSquat;							//! しゃがんでいるかどうか保存する変数
	bool m_IsMove;							//! 動いているかどうかを保存そる変数

	D3DXVECTOR3 m_CenterPos;				//! プレイヤーの中心点(しゃがんだ時にカメラを下げるために追加)


	std::unique_ptr<FbxMotion<PlayerMotionList>> m_Motion;			//! モーションクラス
	std::unique_ptr<PlayerStateBase>             m_State;			//! プレイヤー状態管理クラス
	std::unique_ptr<PlayerEffect>				 m_PlayerEffect;	//! エフェクトクラス
	
};

#endif