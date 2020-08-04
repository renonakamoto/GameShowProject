#ifndef FBXDRAWER_H_
#define FBXDRAWER_H_

#include "../../Utility/3DHelper.h"

/**
* @brief	Fbxの描画クラス
* @details	FbxManagerで管理されるので利用者がさわる必要はない
*/
class FbxDrawer
{
public:
	/**
	* @brief	コンストラクタ
	*/
	FbxDrawer() {}

	/**
	* @brief	デストラクタ
	*/
	~FbxDrawer() {}

	/**
	* @brief	Fbxの描画
	*/
	void RenderFbxMesh(FBXMeshData* pData_, UCHAR alpha_ = 255);

	// FBXのアニメーション
	// 描画ではないがこの関数を呼ばないとアニメーションできない

	/**
	* @brief	Fbxのアニメーション関数
	* @details	FbxManagerで管理されるので利用者がさわる必要はない
	*/
	void Animate(FBXMeshData* pData_, float sec_);

	/**
	* @brief	Fbxのアニメーション初期化関数
	*/
	void ResetAnimate(FBXMeshData* pData_);

private:

	void Skinning(FBXMeshData* pData_);
	//	ボーン行列の補間
	void MatrixInterporate(D3DXMATRIX& out_, D3DXMATRIX& A_, D3DXMATRIX B_, float rate_);

};

#endif