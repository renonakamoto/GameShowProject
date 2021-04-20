#ifndef FOLLOW_CAMERA_H_
#define FOLLOW_CAMERA_H_

#include "Camera.h"

/**
* @brief 追従カメラクラス
*/
class FollowCamera : public Camera
{
public:
	/**
	* @brief コンストラクタ
	*/
	FollowCamera() :
		m_Distance(0.f),
		m_Yaw(0.f),
		m_Height(9.f),
		m_Offset(DirectX::XMFLOAT3(0.f, 0.f, 0.f)),
		m_FollowObject(nullptr)
	{
		m_Tag = "FollowCamera";
	}

	/**
	* @brief デストラクタ
	*/
	virtual	~FollowCamera()
	{}

	/**
	* @fn void Init()
	* @brief 初期化関数
	* @details プロジェクション行列の作成を行う
	*/
	void Init()override;

	/**
	* @fn void Update()
	* @brief 更新関数
	* @details オブジェクトの位置やマウスの移動量などで、カメラ行列を作成する
	*/
	void Update() override;

	/**
	* @fn void SetFollowObject(GameObject* object_)
	* @brief 追従するオブジェクトをセットする関数
	* @param[in] object_ 追従させたいオブジェクト
	*/
	void SetFollowObject(GameObject* object_) { m_FollowObject = object_; }

	/**
	* @fn void SetDistance(float distance_)
	* @brief オブジェクトとの距離をセットする関数
	* @param[in] distance_ 距離
	*/
	void SetDistance(float distance_) { m_Distance = distance_; }
	
	/**
	* @fn void SetOffset(DirectX::XMFLOAT3 offset_)
	* @brief 注視点からのオフセット値をセットする関数
	* @param[in] offset_ オフセット値
	* @details 注視点がオブジェクトの原点になるので、オフセット値で注視点を変えることができる
	*/
	void SetOffset(DirectX::XMFLOAT3 offset_) { m_Offset = offset_; }

private:
	float m_Distance;				//! オブジェクトとの距離
	float m_Yaw;					//! Y軸回転の角度
	float m_Height;					//! カメラの高さ
	DirectX::XMFLOAT3 m_Offset;		//! オブジェクトの原点が注視点になるのでそれを移動させるオフセット値
	GameObject* m_FollowObject;		//! 追従するオブジェクト
};

#endif