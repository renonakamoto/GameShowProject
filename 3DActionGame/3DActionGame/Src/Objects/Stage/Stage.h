#ifndef STAGE_H_
#define STAGE_H_

#include "../../ObjectManager/Object3D.h"
#include "../../ObjectManager/ShadowMapObject.h"
#include "../../Model/ObjFileStrage.h"

/**
* @brief ステージクラス
*/
class Stage : public ShadowMapObject
{
	static const int STAGE_WIETH     = 1200; //! ステージの横幅
	static const int STAGE_HEIGHT    = 1200; //! ステージの縦幅
	static const int STAGE_SPLITNUM  = 15;	 //! ステージの分割数

public:
	/**
	* @brief コンストラクタ
	*/
	Stage() :
		m_Model(nullptr),
		m_CellSize(0)
	{
		m_Tag = "Stage";
		m_Model = ObjFileStrage::GetInstance()->GetModel("Stage");
		if (m_Model)
		{
			CreateSplitMapData();
		}
	}

	/**
	* @brief コンストラクタ
	*/
	~Stage()
	{
		Release();
	}

	/**
	* @fn void Init()
	* @brief 初期化関数
	*/
	void Init() override
	{}

	/**
	* @fn void Update()
	* @brief 更新関数
	*/
	void Update() override
	{}

	/**
	* @fn void Draw()
	* @brief 描画関数
	*/
	void Draw() override;

	/**
	* @fn void Draw()
	* @brief シャドウマップ描画関数
	*/
	void DrawShadowMap() override;
	
	/**
	* @fn float GetPolygonHeight(DirectX::XMFLOAT3 pos_)
	* @brief ある座標のマップのポリゴンの高さを返す関数
	* @param[in] pos_ 高さを調べたい座標
	* @return float マップのポリゴンの高さ
	* @details マップの範囲にいなければ-100.fを返す
	*/
	float GetPolygonHeight(DirectX::XMFLOAT3 pos_) const;

	/**
	* @fn bool IntersectRayAndMap(DirectX::XMFLOAT3 rayOrigin_, DirectX::XMFLOAT3 rayDistance_, float& height_)
	* @brief レイとステージが当たっているかを判定する関数
	* @param[in] rayOrigin_ レイの原点
	* @param[in] rayDistance_ 終点までのベクトル
	* @param[out] height_ 当たった際のポリゴンの高さ
	* @return bool 当たっているかどうかを真偽で返す
	*/
	bool IntersectRayAndStage(DirectX::XMFLOAT3 rayOrigin_, DirectX::XMFLOAT3 rayDistance_, float& height_);
	
private:
	/**
	* @fn void CreateSplitMapData()
	* @brief ステージを分割する関数
	* @details ステージとの当たり判定を軽くするためにポリゴンを分割する
	*/
	void CreateSplitMapData();

	/**
	* @fn void Release()
	* @brief 解放関数
	*/
	void Release() override
	{}

private:
	ObjModel*			 m_Model;											//! ステージのモデル
	std::vector<CVertex> m_MapData[STAGE_SPLITNUM + 1][STAGE_SPLITNUM + 1];	//! 分割したポリゴンを保存する変数
	float				 m_CellSize;										//! ステージを分割した際の1マスのサイズ
};

#endif