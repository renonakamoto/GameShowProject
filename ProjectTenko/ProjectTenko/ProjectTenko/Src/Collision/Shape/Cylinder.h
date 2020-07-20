#ifndef CYLINDER_H_
#define CYLINDER_H_

#include "Shape.h"
#include <d3dx9.h>

/**
* @brief 円柱クラス
*/
class CylinderShape : public Shape
{
public:
	/**
	* @brief コンストラクタ
	*/
	CylinderShape(float radius_, float height_):
		m_Radius(radius_),
		m_Height(height_),
		m_CenterPos(D3DXVECTOR3())
	{}

	/**
	* @brief デストラクタ
	*/
	virtual ~CylinderShape() {}

	/**
	* @brief コリジョン更新関数
	* @details オブジェクトの座標が変わった時に当たり判定用オブジェクトの座標も変更する
	* @param[in] pos_ オブジェクトの座標
	*/
	void Update(const D3DXVECTOR3& pos_) override {
		m_CenterPos = pos_;
	}

	/**
	* @brief 自身の形状を返す関数
	* @return SHAPE_TYPE
	*/
	SHAPE_TYPE GetType() const       override { return SHAPE_TYPE::Shape_Cylinder; }

	/**
	* @brief 自身の座標を返す関数
	* @return SHAPE_TYPE
	*/
	D3DXVECTOR3 GetPos() const override { return m_CenterPos; }

	/**
	* @brief 半径を返す関数
	* @return float 
	*/
	float GetRadius() const			 override { return m_Radius; }

	/**
	* @brief 高さを返す関数
	* @return float
	*/
	float GetHeight() const			 override { return m_Height; }

private:
	D3DXVECTOR3 m_CenterPos;	//! 中心点
	float       m_Radius;		//! 半径
	float       m_Height;		//! 高さ

};

#endif