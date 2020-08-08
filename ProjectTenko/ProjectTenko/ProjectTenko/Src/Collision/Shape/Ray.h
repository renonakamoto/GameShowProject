#ifndef RAY_H_
#define RAY_H_

#include "Shape.h"
#include <d3dx9.h>

/**
* @brief レイクラス
*/
class Ray : public Shape
{
public:
	/**
	* @brief コンストラクタ
	*/
	Ray():
		m_Origin(D3DXVECTOR3()),
		m_Delta(D3DXVECTOR3())
	{}

	/**
	* @brief コンストラクタ
	*/
	Ray(D3DXVECTOR3 origin_, D3DXVECTOR3 delta_):
		m_Origin(origin_),
		m_Delta(delta_)
	{}

	/**
	* @brief デストラクタ
	*/
	~Ray(){}

	/**
	* @brief 空関数
	*/
	virtual void Update(const D3DXVECTOR3& pos_) override {}

	/**
	* @brief レイの情報をセットする関数
	* @param[in] origin_ 光線の原点
	* @param[in] delta_  光線の長さと向き
	*/
	void SetRay(D3DXVECTOR3 origin_, D3DXVECTOR3 delta_) override
	{
		m_Origin = origin_;
		m_Delta  = delta_;
	}

	/**
	* @brief 自身の形状を返す関数
	* @return SHAPE_TYPE
	*/
	virtual SHAPE_TYPE GetType() const override { return SHAPE_TYPE::Shape_Ray; }

	/**
	* @brief 自身の座標(中心点)を返す関数
	* @return D3DXVECTOR3
	*/
	D3DXVECTOR3 GetPos() const override   { return m_Origin; }

	/**
	* @brief 光線の原点を返す関数
	* @return D3DXVECTOR3
	*/
	D3DXVECTOR3 GetOrigin()const  { return m_Origin; }

	/**
	* @brief 光線の長さと向きを返す関数
	* @return D3DXVECTOR3
	*/
	D3DXVECTOR3 GetDelta()const   { return m_Delta;  }

private:
	D3DXVECTOR3 m_Origin;	//! 光線の原点
	D3DXVECTOR3 m_Delta;	//! 光線の長さと向き
	
};

#endif