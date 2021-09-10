#ifndef SHAPE_OBB_H_
#define SHAPE_OBB_H_

#include <DirectXMath.h>
#include "../Shape3D.h"
#include "../../../../Model/ObjFileStrage.h"

/**
* @brief OBBクラス
*/
class ShapeOBB : public Shape3D
{
public:
	/**
	* @brief コンストラクタ
	*/
	ShapeOBB() :
		ShapeOBB(DirectX::XMFLOAT3(0.f, 0.f, 0.f), 1.f, 1.f, 1.f)
	{
	}

	/**
	* @brief コンストラクタ
	* @param[in] pos_ 中心座標
	* @param[in] lengthX_ 中心点からのX軸の長さ
	* @param[in] lengthY_ 中心点からのY軸の長さ
	* @param[in] lengthZ_ 中心点からのZ軸の長さ
	*/
	ShapeOBB(DirectX::XMFLOAT3 pos_, float lengthX_, float lengthY_, float lengthZ_) :
		m_OBB(nullptr),
		m_Pos(pos_),
		m_Length{ lengthX_ , lengthY_ , lengthZ_ },
		m_NormalDirect{ DirectX::XMFLOAT3(1.f, 0.0f, 0.0f), 
					    DirectX::XMFLOAT3(0.f, 1.0f, 0.0f), 
						DirectX::XMFLOAT3(0.f, 0.0f, 1.0f) }
	{
		m_OBB = ObjFileStrage::GetInstance()->GetModel("Cube");
	}

	/**
	* @brief デストラクタ
	*/
	~ShapeOBB()
	{}

public:
	/**
	* @fn bool HitTest(Shape3D& shape_)
	* @brief 引数の形状と当たり判定を行う関数
	* @param[in] shape_ 形状
	* @return bool 当たっているかどうかを真偽で返す
	* @details ダブルディスパッチで形状を特定して、当たり判定を行う
	*/
	bool HitTest(const Shape3D& shape_) const override;

	/**
	* @fn bool HitTest(ShapeOBB& shape_)
	* @brief OBB同士の当たり判定を行う関数
	* @param[in] shape_ OBB
	* @return bool 当たっているかどうかを真偽で返す
	*/
	bool HitTest(const ShapeOBB& shape_)const override;

public:
	/**
	* @fn void Draw()
	* @brief OBBの描画関数
	*/
	void Draw()override;

public:
	DirectX::XMFLOAT3 m_Pos;				//! 中心座標
	DirectX::XMFLOAT3 m_NormalDirect[3];	//!	中心座標から各軸の向きベクトル(単位ベクトル)
	float			  m_Length[3];			//! 各軸の長さ
	

private:
	/**
	* @fn float LenSegOnSeparateAxis(DirectX::XMFLOAT3& spe_, DirectX::XMFLOAT3& e1_, DirectX::XMFLOAT3& e2_, DirectX::XMFLOAT3* e3_)
	* @brief 分離軸に投影された軸成分から投影線分の長さを算出する関数
	* @param[in] spe_ 分離軸 (標準化しておく必要がある)
	* @param[in] e1_ 軸1
	* @param[in] e2_ 軸2
	* @param[in] e3_ 軸3
	* @return float 長さ
	*/
	float LenSegOnSeparateAxis(DirectX::XMFLOAT3& spe_, DirectX::XMFLOAT3& e1_, DirectX::XMFLOAT3& e2_, DirectX::XMFLOAT3* e3_ = nullptr) const;

private:
	ObjModel* m_OBB;	//! モデル
	
};

#endif