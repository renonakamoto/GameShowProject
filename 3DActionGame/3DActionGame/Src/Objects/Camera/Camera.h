#ifndef CAMERA_H_
#define CAMERA_H_

#include "../../ObjectManager/GameObject.h"

/**
* @brief カメラクラス
*/
class Camera : public GameObject
{
public:
	/**
	* @brief コンストラクタ
	*/
	Camera() :
		Camera(DirectX::XMFLOAT3(0.f, 0.f, 0.f), DirectX::XMFLOAT3(0.f, 0.f, 0.f))
	{}

	/**
	* @brief コンストラクタ
	* @param[in] pos_ 座標
	* @param[in] lookAt_ 注視点
	*/
	Camera(DirectX::XMFLOAT3 pos_, DirectX::XMFLOAT3 lookAt_) :
		GameObject(pos_),
		m_LookAt(lookAt_),
		m_ProjMat(DirectX::XMMatrixIdentity())
	{}
	
	/**
	* @brief デストラクタ
	*/
	~Camera()
	{
		Release();
	}

	/**
	* @fn void Init()
	* @brief 初期化関数
	* @details プロジェクション行列の作成を行う
	*/
	virtual void Init() override;

	/**
	* @fn void Update()
	* @brief 更新関数
	* @details カメラ行列の作成を行う
	*/
	virtual void Update() override;

	/**
	* @fn void Draw()
	* @brief 描画関数
	*/
	virtual void Draw() override
	{}

	/**
	* @fn void SetLookAtPos(DirectX::XMFLOAT3 pos_)
	* @brief 注視点を設定する関数
	* @param[in] pos_ 注視点座標
	*/
	void SetLookAtPos(DirectX::XMFLOAT3 pos_) { m_LookAt = pos_; }

	/**
	* @fn DirectX::XMFLOAT3 GetFowardNormal()
	* @brief カメラの前向きベクトルを返す関数
	* @return DirectX::XMFLOAT3 カメラの前方向の単位ベクトル
	*/
	DirectX::XMFLOAT3 GetFowardNormal();

	/**
	* @fn DirectX::XMFLOAT3 GetLeftNormal()
	* @brief カメラの左向きベクトルを返す関
	* @return DirectX::XMFLOAT3 カメラの左方向の単位ベクトル
	*/
	DirectX::XMFLOAT3 GetLeftNormal();
	
protected:
	/**
	* @fn void Release()
	* @brief 解放関数
	*/
	virtual void Release() override
	{}

protected:
	DirectX::XMFLOAT3 m_LookAt;		//! 注視点
	DirectX::XMMATRIX m_ProjMat;	//! プロジェクション行列
	
};

#endif