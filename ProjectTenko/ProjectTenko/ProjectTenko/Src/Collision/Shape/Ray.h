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
	Ray():
		m_Origin(D3DXVECTOR3()),
		m_Delta(D3DXVECTOR3())
	{}

	Ray(D3DXVECTOR3 origin_, D3DXVECTOR3 delta_):
		m_Origin(origin_),
		m_Delta(delta_)
	{}

	~Ray(){}

	virtual SHAPE_TYPE GetType() const override { return SHAPE_TYPE::Shape_Ray; }
	virtual void Update(const D3DXVECTOR3& pos_) override {}

	void SetRay(D3DXVECTOR3 origin_, D3DXVECTOR3 delta_) override
	{
		m_Origin = origin_;
		m_Delta  = delta_;
	}

	D3DXVECTOR3 GetPos() const override   { return m_Origin; }
	D3DXVECTOR3 GetOrigin()const override { return m_Origin; }
	D3DXVECTOR3 GetDelta()const override  { return m_Delta;  }

private:
	D3DXVECTOR3 m_Origin;	// 光線の原点
	D3DXVECTOR3 m_Delta;	// 光線の長さと向き
	
};

#endif