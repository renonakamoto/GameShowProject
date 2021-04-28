#ifndef CALCULATION_H_
#define CALCULATION_H_

#include <d3d11.h>
#include <DirectXMath.h>
#include "../CollisionManager/Shape/2D/Rect/Rect.h"


/**
* @brief 計算を行うクラス
*/
class Calculation
{
public:
	/**
	* @fn DirectX::XMFLOAT2 Add(DirectX::XMFLOAT2 a_, DirectX::XMFLOAT2 b_)
	* @brief XMFLOAT2同士の加算を行う関数
	* @param[in] a_ XMFLOAT2
	* @param[in] b_ XMFLOAT2
	* @return DirectX::XMFLOAT2 加算結果を返す
	*/
	static DirectX::XMFLOAT2 Add(DirectX::XMFLOAT2 a_, DirectX::XMFLOAT2 b_);

	/**
	* @fn DirectX::XMFLOAT3 Add(DirectX::XMFLOAT3 a_, DirectX::XMFLOAT3 b_)
	* @brief XMFLOAT3同士の加算を行う関数
	* @param[in] a_ XMFLOAT3
	* @param[in] b_ XMFLOAT3
	* @return DirectX::XMFLOAT3 加算結果を返す
	*/
	static DirectX::XMFLOAT3 Add(DirectX::XMFLOAT3 a_, DirectX::XMFLOAT3 b_);
	
	/**
	* @fn DirectX::XMFLOAT2 Sub(DirectX::XMFLOAT2 a_, DirectX::XMFLOAT2 b_)
	* @brief XMFLOAT2同士の減算を行う関数
	* @param[in] a_ XMFLOAT2
	* @param[in] b_ XMFLOAT2
	* @return DirectX::XMFLOAT2 減算結果を返す
	*/
	static DirectX::XMFLOAT2 Sub(DirectX::XMFLOAT2 a_, DirectX::XMFLOAT2 b_);

	/**
	* @fn DirectX::XMFLOAT3 Sub(DirectX::XMFLOAT3 a_, DirectX::XMFLOAT3 b_)
	* @brief XMFLOAT3同士の減算を行う関数
	* @param[in] a_ XMFLOAT3
	* @param[in] b_ XMFLOAT3
	* @return DirectX::XMFLOAT3 減算結果を返す
	*/
	static DirectX::XMFLOAT3 Sub(DirectX::XMFLOAT3 a_, DirectX::XMFLOAT3 b_);
	
	/**
	* @fn DirectX::XMFLOAT2 Mul(DirectX::XMFLOAT2 a_, float b_)
	* @brief XMFLOAT2のスカラー倍を行う関数
	* @param[in] a_ ベース
	* @param[in] b_ 倍数
	* @return DirectX::XMFLOAT2 スカラー倍の結果を返す
	*/
	static DirectX::XMFLOAT2 Mul(DirectX::XMFLOAT2 a_, float b_);

	/**
	* @fn DirectX::XMFLOAT3 Mul(DirectX::XMFLOAT3 a_, float b_)
	* @brief XMFLOAT3のスカラー倍を行う関数
	* @param[in] a_ ベース
	* @param[in] b_ 倍数
	* @return DirectX::XMFLOAT3 スカラー倍の結果を返す
	*/
	static DirectX::XMFLOAT3 Mul(DirectX::XMFLOAT3 a_, float b_);

	/**
	* @fn DirectX::XMFLOAT3 Mul(DirectX::XMFLOAT3 a_, DirectX::XMFLOAT3 b_)
	* @brief XMFLOAT3同士の乗算を行う関数
	* @param[in] a_ XMFLOAT3
	* @param[in] b_ XMFLOAT3
	* @return DirectX::XMFLOAT3 乗算の結果を返す
	* @details 各成分を掛けた結果を返す
	*/
	static DirectX::XMFLOAT3 Mul(DirectX::XMFLOAT3 a_, DirectX::XMFLOAT3 b_);

	/**
	* @fn DirectX::XMFLOAT2 Div(DirectX::XMFLOAT2 a_, float b_)
	* @brief XMFLOAT2の各成分の除算を行う関数
	* @param[in] a_ ベース
	* @param[in] b_ 割る数
	* @return DirectX::XMFLOAT2 除算の結果を返す
	*/
	static DirectX::XMFLOAT2 Div(DirectX::XMFLOAT2 a_, float b_);

	/**
	* @fn DirectX::XMFLOAT3 Div(DirectX::XMFLOAT3 a_, float b_)
	* @brief XMFLOAT3の各成分の除算を行う関数
	* @param[in] a_ ベース
	* @param[in] b_ 割る数
	* @return DirectX::XMFLOAT3 除算の結果を返す
	*/
	static DirectX::XMFLOAT3 Div(DirectX::XMFLOAT3 a_, float b_);

	/**
	* @fn float Cross(DirectX::XMFLOAT2 a_, DirectX::XMFLOAT2 b_)
	* @brief 外積を行う関数
	* @param[in] a_ 要素1
	* @param[in] b_ 要素2
	* @return float 外積の結果を返す
	*/
	static float Cross(DirectX::XMFLOAT2 a_, DirectX::XMFLOAT2 b_);

	/**
	* @fn DirectX::XMFLOAT3 Cross(DirectX::XMFLOAT3 a_, DirectX::XMFLOAT3 b_)
	* @brief 外積を行う関数
	* @param[in] a_ 要素1
	* @param[in] b_ 要素2
	* @return DirectX::XMFLOAT3 外積の結果を返す
	*/
	static DirectX::XMFLOAT3 Cross(DirectX::XMFLOAT3 a_, DirectX::XMFLOAT3 b_);

	/**
	* @fn float Dot(DirectX::XMFLOAT2 a_, DirectX::XMFLOAT2 b_)
	* @brief 内積を行う関数
	* @param[in] a_ 要素1
	* @param[in] b_ 要素2
	* @return float 内積の結果を返す
	*/
	static float Dot(DirectX::XMFLOAT2 a_, DirectX::XMFLOAT2 b_);

	/**
	* @fn float Dot(DirectX::XMFLOAT3 a_, DirectX::XMFLOAT3 b_)
	* @brief 内積を行う関数
	* @param[in] a_ 要素1
	* @param[in] b_ 要素2
	* @return float 内積の結果を返す
	*/
	static float Dot(DirectX::XMFLOAT3 a_, DirectX::XMFLOAT3 b_);

	/**
	* @fn DirectX::XMFLOAT2 Normalize(DirectX::XMFLOAT2 vec_)
	* @brief ベクトルの正規化を行う関数
	* @param[in] vec_ ベクトル
	* @return DirectX::XMFLOAT2 正規化されたベクトル
	*/
	static DirectX::XMFLOAT2 Normalize(DirectX::XMFLOAT2 vec_);

	/**
	* @fn DirectX::XMFLOAT3 Normalize(DirectX::XMFLOAT3 vec_)
	* @brief ベクトルの正規化を行う関数
	* @param[in] vec_ ベクトル
	* @return DirectX::XMFLOAT3 正規化されたベクトル
	*/
	static DirectX::XMFLOAT3 Normalize(DirectX::XMFLOAT3 vec_);

	/**
	* @fn float Length(DirectX::XMFLOAT2 vec_)
	* @brief ベクトルの長さを算出する関数
	* @param[in] vec_ ベクトル
	* @return float ベクトルの長さ
	*/
	static float Length(DirectX::XMFLOAT2 vec_);

	/**
	* @fn float Length(DirectX::XMFLOAT3 vec_)
	* @brief ベクトルの長さを算出する関数
	* @param[in] vec_ ベクトル
	* @return float ベクトルの長さ
	*/
	static float Length(DirectX::XMFLOAT3 vec_);

	/**
	* @fn DirectX::XMFLOAT3 InvVec(DirectX::XMFLOAT3 vec_)
	* @brief 逆ベクトルを返す関数
	* @param[in] vec_ ベクトル
	* @return float 逆ベクトル
	*/
	static DirectX::XMFLOAT3 InvVec(DirectX::XMFLOAT3 vec_);
	
	/**
	* @fn DirectX::XMFLOAT2 InvVec(DirectX::XMFLOAT2 vec_)
	* @brief 逆ベクトルを返す関数
	* @param[in] vec_ ベクトル
	* @return float 逆ベクトル
	*/
	static DirectX::XMFLOAT2 InvVec(DirectX::XMFLOAT2 vec_);

	/**
	* @fn void Clamp(float& value_, float min_, float max_)
	* @brief value_を最小値から最大値以内に収める関数
	* @param[out] value_ クランプを掛ける値
	* @param[in] min_ 最小値
	* @param[in] max_ 最大値
	*/
	static void Clamp(float& value_, float min_, float max_);

	/**
	* @fn DirectX::XMFLOAT3 Lerp(DirectX::XMFLOAT3 a_, DirectX::XMFLOAT3 b_, float t)
	* @brief ベクトルAからベクトルBへの線形補間を行う関数
	* @param[in] a_ ベクトルA
	* @param[in] b_ ベクトルB
	* @param[in] t_ 時間(0.0f ～ 1.0fの範囲)
	* @return DirectX::XMFLOAT3 補間された結果
	*/
	static DirectX::XMFLOAT3 Lerp(DirectX::XMFLOAT3 a_, DirectX::XMFLOAT3 b_, float t);

	/**
	* @fn bool HitRectAndPoint(Rect rect_, float x_, float y_)
	* @brief 矩形と点の当たり判定行う関数
	* @param[in] rect_ 矩形
	* @param[in] x_ 点のX軸座標
	* @param[in] y_ 点のY軸座標
	* @return bool 当たったかどうかを真偽で返す
	*/
	static bool HitRectAndPoint(Rect rect_, float x_, float y_);

	/**
	* @fn float CalcPointToPlaneDistance(DirectX::XMFLOAT3 p_, DirectX::XMFLOAT3 pA_, DirectX::XMFLOAT3 pB_)
	* @brief 点と面の距離を算出する関数
	* @param[in] p_ 点の座標
	* @param[in] pA_ 面を表すベクトルA
	* @param[in] pB_ 面を表すベクトルB
	* @return float 距離
	*/
	static float CalcPointToPlaneDistance(DirectX::XMFLOAT3 p_, DirectX::XMFLOAT3 pA_, DirectX::XMFLOAT3 pB_);

	/**
	* @fn bool HitTriangleAndPoint(DirectX::XMFLOAT2 a_, DirectX::XMFLOAT2 b_, DirectX::XMFLOAT2 c_, DirectX::XMFLOAT2 p_)
	* @brief 三角形と点の当たり判定
	* @param[in] a_ 三角形の頂点A
	* @param[in] b_ 三角形の頂点B
	* @param[in] c_ 三角形の頂点C
	* @param[in] p_ 点軸座標
	* @return bool 当たったかどうかを真偽で返す
	*/
	static bool HitTriangleAndPoint(DirectX::XMFLOAT2 a_, DirectX::XMFLOAT2 b_, DirectX::XMFLOAT2 c_, DirectX::XMFLOAT2 p_);
	
	/**
	* @fn bool HitRayAndPlane(DirectX::XMFLOAT3 rayOrigin_, DirectX::XMFLOAT3 rayDistance_, DirectX::XMFLOAT3 pA_, DirectX::XMFLOAT3 pB_)
	* @brief レイと面の当たり判定を行う関数
	* @param[in] rayOrigin_ レイの原点
	* @param[in] rayDistance_ 原点から終点へのベクトル
	* @param[in] pA_ 面を表すベクトルA
	* @param[in] pB_ 面を表すベクトルB
	* @return bool 当たっているかどうかを真偽で返す
	*/
	static bool HitRayAndPlane(DirectX::XMFLOAT3 rayOrigin_, DirectX::XMFLOAT3 rayDistance_, DirectX::XMFLOAT3 pA_, DirectX::XMFLOAT3 pB_);

	/**
	* @fn bool IntersectRayAndTriangle(DirectX::XMFLOAT3 rayOrigin_, DirectX::XMFLOAT3 rayDistance_, DirectX::XMFLOAT3 a_, DirectX::XMFLOAT3 b_, DirectX::XMFLOAT3 c_, DirectX::XMFLOAT3& intersectPos_)
	* @brief レイと三角形が交差しているかをの判定を行う関数
	* @param[in] rayOrigin_ レイの原点
	* @param[in] rayDistance_ 原点から終点へのベクトル
	* @param[in] a_ 三角形の頂点A
	* @param[in] b_ 三角形の頂点B
	* @param[in] c_ 三角形の頂点C
	* @param[out] intersectPos_ 交差位置
	* @return bool 当たっているかどうかを真偽で返す
	*/
	static bool IntersectRayAndTriangle(DirectX::XMFLOAT3 rayOrigin_, DirectX::XMFLOAT3 rayDistance_, DirectX::XMFLOAT3 a_, DirectX::XMFLOAT3 b_, DirectX::XMFLOAT3 c_, DirectX::XMFLOAT3& intersectPos_);

private:
	/**
	* @brief コンストラクタ
	*/
	Calculation()
	{}

	/**
	* @brief デストラクタ
	*/
	~Calculation()
	{}
};

#endif