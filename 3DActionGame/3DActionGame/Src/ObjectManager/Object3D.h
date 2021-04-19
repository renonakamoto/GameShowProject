#ifndef OBJECT3D_H_
#define OBJECT3D_H_

#include "GameObject.h"
#include "../CollisionManager/Shape/3D/Shape3D.h"

/**
* @brief 3Dオブジェクトの基底クラス
*/
class Object3D : public GameObject
{
public:
	/**
	* @brief コンストラクタ
	*/
	Object3D():
		Object3D(DirectX::XMFLOAT3(0.f, 0.f, 0.f),
				 DirectX::XMFLOAT3(0.f, 0.f, 0.f), 
				 DirectX::XMFLOAT3(1.f, 1.f, 1.f))
	{}

	/**
	* @brief コンストラクタ
	* @param[in] pos_ 座標
	*/
	Object3D(DirectX::XMFLOAT3 pos_) :
		Object3D(pos_, DirectX::XMFLOAT3(0.f, 0.f, 0.f), DirectX::XMFLOAT3(1.f, 1.f, 1.f))
	{}

	/**
	* @brief コンストラクタ
	* @param[in] pos_ 座標
	* @param[in] rot_ 回転 (度数法)
	* @param[in] scale_ 拡縮倍率
	*/
	Object3D(DirectX::XMFLOAT3 pos_, DirectX::XMFLOAT3 rot_, DirectX::XMFLOAT3 scale_) :
		GameObject(pos_, rot_, scale_),
		m_Shape(nullptr)
	{}

	/**
	* @brief デストラクタ
	*/
	virtual ~Object3D()
	{
		Release();
	}

	/**
	* @fn void Init()
	* @brief 初期化関数
	* @details 継承先で定義し、オブジェクトの初期化を行う
	*/
	virtual void Init() = 0;

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
	virtual void Draw() = 0;

protected:

	/**
	* @fn void Release()
	* @brief 解放関数
	* @details 継承先で定義し、解放処理を行う
	*/
	virtual void Release()
	{
		if (m_Shape)
		{
			delete m_Shape;
			m_Shape = nullptr;
		}
	}
	
public:
	/**
	* @fn Shape3D* GetShape()
	* @brief 形状を返す関数
	* @return Shape3D* 形状クラスのポインタ
	*/
	Shape3D* GetShape() { return m_Shape; }

protected:
	Shape3D* m_Shape;	//! 形状の基底クラス
	
};


#endif