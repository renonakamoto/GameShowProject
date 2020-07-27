#ifndef SHAPE_H_
#define SHAPE_H_

#include <d3dx9.h>

enum class SHAPE_TYPE
{
	Shape_AABB,
	Shape_Cylinder,
	Shape_Ray,

	Shape_Type_Num,
};

/**
* @brief 当たり判定に使う形の基底クラス
*/
class Shape
{
public:
	/**
	* @brief デストラクタ
	*/
	virtual ~Shape() {}

	/**
	* @brief コリジョン更新関数
	* @details オブジェクトの座標が変わった時に当たり判定用オブジェクトの座標も変更する
	* @param[in] pos_ オブジェクトの座標
	*/
	virtual void Update(const D3DXVECTOR3& pos_) = 0;

	/**
	* @brief 形を返す関数
	*/
	virtual SHAPE_TYPE GetType() const = 0;

	/**
	* @brief 判定用オブジェクトの座標を返す
	*/
	virtual D3DXVECTOR3 GetPos()const = 0;

public:

	virtual D3DXVECTOR3 GetMin() const { return D3DXVECTOR3(); }
	virtual D3DXVECTOR3 GetMax() const { return D3DXVECTOR3(); }

public:
	
	virtual D3DXVECTOR3 GetCenterPos() const { return D3DXVECTOR3(); }
	virtual float GetRadius() const { return 0.f; }
	virtual float GetHeight() const { return 0.f; }
	virtual void  SetRay(D3DXVECTOR3 origin_, D3DXVECTOR3 delta_){}

public:
	virtual D3DXVECTOR3 GetOrigin()const { return D3DXVECTOR3(); }
	virtual D3DXVECTOR3 GetDelta()const  { return D3DXVECTOR3(); }
};

#endif