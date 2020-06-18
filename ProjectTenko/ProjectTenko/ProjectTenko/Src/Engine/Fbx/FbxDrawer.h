#ifndef FBXDRAWER_H_
#define FBXDRAWER_H_

#include "../../Utility/3DHelper.h"

// FBXの描画関数
// 利用者が触る必要はない
class FbxDrawer
{
public:
	// コンストラクタ
	FbxDrawer() {}
	// デストラクタ
	~FbxDrawer() {}

	// FBXメッシュの描画
	void RenderFbxMesh(FBXMeshData* pData_, UCHAR alpha_ = 255);

	// FBXのアニメーション
	// 描画ではないがこの関数を呼ばないとアニメーションできない
	void Animate(FBXMeshData* pData_, float sec_);

	// アニメーション(キーフレーム)をリセットする
	void ResetAnimate(FBXMeshData* pData_);

private:
	// おそらくモーションにかかわる処理
	void Skinning(FBXMeshData* pData_);
	//	ボーン行列の補間
	void MatrixInterporate(D3DXMATRIX& out_, D3DXMATRIX& A_, D3DXMATRIX B_, float rate_);

};

#endif