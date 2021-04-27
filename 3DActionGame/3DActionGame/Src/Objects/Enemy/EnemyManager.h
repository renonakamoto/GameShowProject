#ifndef ENEMYMANAGER_H_
#define ENEMYMANAGER_H_

#include "../../ObjectManager/GameObject.h"
#include "Enemy.h"

/**
* @brief エネミー管理クラス
*/
class EnemyManager : public ShadowMapObject
{
public:
	/**
	* @brief コンストラクタ
	*/
	EnemyManager()
	{}

	/**
	* @brief デストラクタ
	*/
	~EnemyManager() final
	{
		Release();
	}
	
	/**
	* @fn void Init()
	* @brief 初期化関数
	* @details エネミーの生成、初期化を行う
	*/
	void Init() override;

	/**
	* @fn void Update()
	* @brief 更新関数
	* @details エネミーリストの更新を行う
	*/
	void Update() override;

	/**
	* @fn void Draw()
	* @brief 描画関数
	* @details エネミーリストの描画を行う
	*/
	void Draw() override;

	void DrawShadowMap() override;

private:
	/**
	* @fn void Erase(int idx_)
	* @brief リストから指定した要素番号のエネミーを削除する関数
	* @param[in] idx_ 削除したいエネミーの要素番号
	*/
	void Erase(int idx_);

	/**
	* @fn void Release()
	* @brief 解放関数
	*/
	void Release();

private:
	std::vector<Enemy*> m_Enemies;	//! エネミー配列
	
};

#endif