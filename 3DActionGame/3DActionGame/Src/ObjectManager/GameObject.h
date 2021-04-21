#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include <DirectXMath.h>
#include "ObjectBase.h"

/**
* @brief ゲームオブジェクト基底クラス
*/
class GameObject : public ObjectBase
{
public:
	/**
	* @brief コンストラクタ
	*/
	GameObject() :
		GameObject(DirectX::XMFLOAT3(0.f, 0.f, 0.f),
				   DirectX::XMFLOAT3(0.f, 0.f, 0.f), 
				   DirectX::XMFLOAT3(1.f, 1.f, 1.f))
	{}

	/**
	* @brief コンストラクタ
	* @param[in] pos_ 座標
	*/
	GameObject(DirectX::XMFLOAT3 pos_) :
		GameObject(pos_, DirectX::XMFLOAT3(0.f, 0.f, 0.f), DirectX::XMFLOAT3(1.f, 1.f, 1.f))
	{}

	/**
	* @brief コンストラクタ
	* @param[in] pos_ 座標
	* @param[in] rot_ 回転 (度数法)
	* @param[in] scale_ 拡縮倍率
	*/
	GameObject(DirectX::XMFLOAT3 pos_, DirectX::XMFLOAT3 rot_, DirectX::XMFLOAT3 scale_) :
		m_Pos(pos_),
		m_Rot(rot_),
		m_Scale(scale_)
	{}

	/**
	* @brief デストラクタ
	*/
	virtual ~GameObject()
	{}

	/**
	* @fn void Init()
	* @brief 初期化関数
	* @details 継承先で定義し、オブジェクトの初期化を行う
	*/
	virtual void Init()   = 0;

	/**
	* @fn void Update()
	* @brief 更新関数
	* @details 継承先で定義し、オブジェクトの更新を行う
	*/
	virtual void Update() = 0;

	/**
	* @fn void Draw()
	* @brief 描画関数
	* @details 継承先で定義し、オブジェクトの描画を行う
	*/
	virtual void Draw()   = 0;

public:
	/**
	* @fn void SetPos(DirectX::XMFLOAT3 pos_)
	* @brief ポジションセット関数
	* @param[in] pos_ 座標
	*/
	void SetPos(DirectX::XMFLOAT3 pos_) { m_Pos = pos_; }

	/**
	* @fn DirectX::XMFLOAT3 GetPos()
	* @brief 座標を返す関数
	* @return DirectX::XMFLOAT3 座標
	*/
	DirectX::XMFLOAT3 GetPos() { return m_Pos; }

	/**
	* @fn void SetRot(DirectX::XMFLOAT3 rot_)
	* @brief 回転セット関数
	* @param[in] pos_ 回転 (度数法)
	*/
	void SetRot(DirectX::XMFLOAT3 rot_) { m_Rot = rot_; }

	/**
	* @fn DirectX::XMFLOAT3 GetRot()
	* @brief 回転(度数)を返す関数
	* @return DirectX::XMFLOAT3 回転(度数)
	*/
	DirectX::XMFLOAT3 GetRot() { return m_Rot; }

	/**
	* @fn void SetScale(DirectX::XMFLOAT3 scale_)
	* @brief スケールセット関数
	* @param[in] pos_ 拡大倍率
	*/
	void SetScale(DirectX::XMFLOAT3 scale_) { m_Scale = scale_; }

	/**
	* @fn DirectX::XMFLOAT3 GetScale()
	* @brief スケールを返す関数
	* @return DirectX::XMFLOAT3 スケール
	*/
	DirectX::XMFLOAT3 GetScale() { return m_Scale; }
	
protected:
	/**
	* @fn void Release()
	* @brief 解放関数
	* @details 継承先で定義し、解放処理を行う
	*/
	virtual void Release() = 0;

protected:
	DirectX::XMFLOAT3 m_Pos;	//! 座標
	DirectX::XMFLOAT3 m_Rot;	//! 回転
	DirectX::XMFLOAT3 m_Scale;	//! 拡大率

};

#endif