#ifndef SHADOW_MAP_OBJECT_H_
#define SHADOW_MAP_OBJECT_H_

#include "Object3D.h"

/**
* @brief シャドウマップを行うオブジェクトの基底クラス
*/
class ShadowMapObject : public Object3D
{
public:
	/**
	* @brief コンストラクタ
	*/
	ShadowMapObject()
	{}

	/**
	* @brief コンストラクタ
	*/
	ShadowMapObject(DirectX::XMFLOAT3 pos_):
		Object3D(pos_)
	{}

	/**
	* @brief コンストラクタ
	*/
	ShadowMapObject(DirectX::XMFLOAT3 pos_, DirectX::XMFLOAT3 rot_, DirectX::XMFLOAT3 scale_):
		Object3D(pos_, rot_, scale_)
	{}

	/**
	* @brief デストラクタ
	*/
	virtual ~ShadowMapObject()
	{}

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

	/**
	* @fn void DrawShadowMap()
	* @brief シャドウマップ用描画関数
	* @details 継承先で定義し、シャドウマップ用レンダーターゲットにオブジェクトの描画を行う
	*/
	virtual void DrawShadowMap() = 0;

private:
	/**
	* @fn void Release()
	* @brief 解放関数
	* @details 継承先で定義し、解放処理を行う
	*/
	virtual void Release() = 0;

};

#endif