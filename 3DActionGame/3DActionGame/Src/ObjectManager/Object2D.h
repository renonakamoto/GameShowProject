#ifndef OBJECT2D_H_
#define OBJECT2D_H_

#include <d3d11.h>
#include "GameObject.h"

/**
* @brief 2Dオブジェクトの基底クラス
*/
class Object2D : public GameObject
{
public:
	/**
	* @brief コンストラクタ
	*/
	Object2D() :
		Object2D(DirectX::XMFLOAT3(0.f, 0.f, 0.f),
				 DirectX::XMFLOAT3(0.f, 0.f, 0.f),
				 DirectX::XMFLOAT3(1.f, 1.f, 1.f))
	{}

	/**
	* @brief コンストラクタ
	* @param[in] pos_ 座標
	*/
	Object2D(DirectX::XMFLOAT3 pos_) :
		GameObject(pos_)
	{}

	/**
	* @brief コンストラクタ
	* @param[in] pos_ 座標
	* @param[in] rot_ 回転 (度数法)
	* @param[in] scale_ 拡縮倍率
	*/
	Object2D(DirectX::XMFLOAT3 pos_, DirectX::XMFLOAT3 rot_, DirectX::XMFLOAT3 scale_) :
		GameObject(pos_, rot_, scale_)
	{}
	
	/**
	* @brief デストラクタ
	*/
	virtual ~Object2D()
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

protected:

	/**
	* @fn void Release()
	* @brief 解放関数
	* @details 継承先で定義し、解放処理を行う
	*/
	virtual void Release() = 0;
	
};

#endif