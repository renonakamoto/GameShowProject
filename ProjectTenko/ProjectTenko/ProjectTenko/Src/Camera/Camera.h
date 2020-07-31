#ifndef CAMERA_H_
#define CAMERA_H_

#include "../Collision/Shape/Shape.h"
#include "../Utility/Singleton.h"
#include <d3dx9.h>

class ObjectBase;

/**
* @brief カメラクラス
* @details 詳細なクラスの説明
*/
class Camera //: public Singleton<Camera>
{
	//friend class Singleton<Camera>;

public:
	/**
	* @brief コンストラクタ
	*/
	Camera();

	/**
	* @brief コンストラクタ
	*/
	Camera(D3DXVECTOR3 pos_, D3DXVECTOR3 lookAt_, D3DXVECTOR3 upVec_, float distance_);

	/**
	* @brief デストラクタ
	*/
	~Camera();

	/**
	* @brief 更新関数
	*/
	void Update();

	/**
	* @brief 対象を見るようにカメラの位置をセットする
	* @param[in] pos_ 対象となるオブジェクト 
	* @param[in] distance_  カメラと離す距離
	*/
	void SetCamera(const D3DXVECTOR3& pos_, float distance_);

	/**
	* @brief 前向きのベクトルを返す関数
	* @return D3DXVECTOR3 前向きベクトル
	*/
	D3DXVECTOR3  GetForwardVec()const;

	/**
	* @brief 左向きのベクトルを返す関数
	* @return D3DXVECTOR3 左向きベクトル
	*/
	D3DXVECTOR3  GetLeftVec()const;

	/**
	* @brief 形状を返す関数
	* @return Shape*
	*/
	Shape* GetShape()const				 { return m_Shape;   }

	/**
	* @brief カメラの座標を返す関数
	* @return D3DXVECTOR3*
	*/
	const D3DXVECTOR3* GetPos()const     { return &m_Pos;    }
	
	/**
	* @brief カメラの注視点を返す関数
	* @return D3DXVECTOR3*
	*/
	const D3DXVECTOR3* GetLookAt()const  { return &m_LookAt; }
	
	/**
	* @brief カメラの上向きベクトルを返す関数
	* @return D3DXVECTOR3*
	*/
	const D3DXVECTOR3* GetUpVec()const   { return &m_UpVec;  }
	
private:
	/**
	* @brief カメラの回転関数
	*/
	void Rotate();

	/**
	* @brief ビュー座標変換
	*/
	void SetViewMatrix();

	/**
	* @brief プロジェクション座標変換
	*/
	void SetProjectionMatrix();

	D3DXVECTOR3 m_Pos;		//! カメラの座標
	D3DXVECTOR3 m_LookAt;	//! 注視点
	D3DXVECTOR3 m_UpVec;	//! カメラの上向きベクトル
	float m_Distance;		//! 距離

	float m_Yaw;			//! X軸回転
	float m_Pitch;			//! Y軸回転

	D3DXVECTOR2 m_Sensitivity;	//! カメラ感度

	Shape* m_Shape;			//! 形状
};

#endif