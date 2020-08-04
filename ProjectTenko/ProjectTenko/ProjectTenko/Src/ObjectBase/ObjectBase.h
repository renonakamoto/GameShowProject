#ifndef OBJECTBASE_H_
#define OBJECTBASE_H_

#include "../Engine/Fbx/FbxManager.h"
#include "../Collision/Shape/Shape.h"
#include <d3dx9.h>
#include <string>
#include <vector>

/**
* @brief オブジェクト基底クラス
*/
class ObjectBase
{
public:
	/**
	* @brief コンストラクタ
	*/
	ObjectBase() :
		m_Pos   (D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
		m_Angle (0.f),
		m_Width (0.f),
		m_Height(0.f),
		m_Depth (0.f)
	{}

	/**
	* @brief コンストラクタ
	*/
	ObjectBase(D3DXVECTOR3 pos_) :
		m_Pos(pos_),
		m_Angle(0.f),
		m_Width(0.f),
		m_Height(0.f),
		m_Depth(0.f)
	{}

	/**
	* @brief コンストラクタ
	*/
	ObjectBase(D3DXVECTOR3 pos_, float width_, float height_, float depth_) :
		m_Pos   (pos_),
		m_Width (width_),
		m_Height(height_),
		m_Depth (depth_),
		m_Angle (0.0f)
	{}

	/**
	* @brief デストラクタ
	*/
	virtual ~ObjectBase() 
	{
		for(size_t i = 0; i < m_Shape.size(); i++)
		{ 
			delete m_Shape[i];
		}

		m_Shape.clear();
	}

	/**
	* @brief 更新関数
	*/
	virtual void Update() {}

	/**
	* @brief 描画関数
	*/
	virtual void Draw() {}

	/**
	* @brief 座標を返す関数
	*/
	D3DXVECTOR3 GetPos() const{ return m_Pos; }

	/**
	* @brief 当たり判定の形状を返す関数
	*/
	std::vector<Shape*> GetShape() const{ return m_Shape; }

	/**
	* @brief 角度を返す関数
	*/
	float GetAngle() const{ return m_Angle; }

protected:

	//! 座標
	D3DXVECTOR3 m_Pos;

	//! 角度
	float		m_Angle;

	//! 横幅
	float		m_Width;

	//! 高さ
	float		m_Height;

	//! 奥行き
	float		m_Depth;

	//! 形状クラス
	std::vector<Shape*> m_Shape;

};

#endif