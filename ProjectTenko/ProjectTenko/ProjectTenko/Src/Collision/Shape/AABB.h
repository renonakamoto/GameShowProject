#ifndef AABB_H_
#define AABB_H_

#include "Shape.h"
#include <d3dx9.h>


/**
* @brief AABBクラス
*/
class AABBShape : public Shape
{
public:
	/**
	* @brief コンストラクタ
	*/
	AABBShape():
		m_Width(0.0f),
		m_Height(0.0f),
		m_Depth(0.0f),
		m_Min(D3DXVECTOR3()),
		m_Max(D3DXVECTOR3())
	{}

	/**
	* @brief コンストラクタ
	*/
	AABBShape(float width_, float height_, float depth_) :
		m_Width (width_),
		m_Height(height_),
		m_Depth (depth_),
		m_Min(D3DXVECTOR3()),
		m_Max(D3DXVECTOR3())
	{}

	/**
	* @brief コンストラクタ
	*/
	AABBShape(D3DXVECTOR3 pos_,float width_, float height_, float depth_) :
		m_Width(width_),
		m_Height(height_),
		m_Depth(depth_),
		m_Min(D3DXVECTOR3()),
		m_Max(D3DXVECTOR3())
	{
		Update(pos_);
	}

	/**
	* @brief デストラクタ
	*/
	virtual ~AABBShape() {}

	/**
	* @brief コリジョン更新関数
	* @details オブジェクトの座標が変わった時に当たり判定用オブジェクトの座標も変更する
	* @param[in] pos_ オブジェクトの座標
	*/
	void Update(const D3DXVECTOR3& pos_) override {
		float half_width  = m_Width  / 2.f;
		float half_height = m_Height / 2.f;
		float half_depth  = m_Depth  / 2.f;

		m_Min = D3DXVECTOR3(pos_.x - half_width, pos_.y - half_height, pos_.z - half_depth);
		m_Max = D3DXVECTOR3(pos_.x + half_width, pos_.y + half_height, pos_.z + half_depth);
	}

	/**
	* @brief 自身の形状を返す関数
	* @return SHAPE_TYPE
	*/
	SHAPE_TYPE GetType() const override { return SHAPE_TYPE::Shape_AABB; }

	/**
	* @brief 自身の座標(中心点)を返す関数
	* @return D3DXVECTOR3
	*/
	D3DXVECTOR3 GetPos() const override { return m_Max / 2; }

	/**
	* @brief 自身の座標の最小値を返す
	* @return D3DXVECTOR3
	*/
	D3DXVECTOR3 GetMin() const override { return m_Min; }

	/**
	* @brief 自身の座標の最大値を返す関数
	* @return D3DXVECTOR3
	*/
	D3DXVECTOR3 GetMax() const override { return m_Max; }

private:
	
	D3DXVECTOR3 m_Min;	//! XYZ軸の最小値
	D3DXVECTOR3 m_Max;	//! XYZ軸の最大値

	float m_Width;		//! 横幅
	float m_Height;		//! 高さ
	float m_Depth;		//! 奥行き

};

#endif