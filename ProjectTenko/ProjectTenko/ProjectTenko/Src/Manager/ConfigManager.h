#ifndef CONFIGMANAGER_H_
#define CONFIGMANAGER_H_

#include "../Utility/SingletonTemplate.h"

/**
* @brief ゲームの設定管理クラス
* @details 
*/
class GameConfigManager
{
	friend MySingletonTemplate::SingletonTemplate<GameConfigManager>;
public:
	
	/**
	* @brief ボタンが離された瞬間かの情報取得関数
	* @param[in] flip マウスを反転させる : true　マウスを反転させない : false
	*/
	void SetMouseFlip(bool flip) { m_IsMouseFlip = flip; }

	/**
	* @brief マウスが反転しているかどうかを返す
	* @return bool マウス反転している:true マウス反転していない:false
	*/
	bool IsMouseFlip()const		 { return m_IsMouseFlip; }
	
private:

	/**
	* @brief コンストラクタ
	*/
	GameConfigManager()
	{
		m_IsMouseFlip = false;
	}

	/**
	* @brief デストラクタ
	*/
	~GameConfigManager(){}


	bool m_IsMouseFlip;	//! マウスの反転情報を保存する変数
	


};

typedef MySingletonTemplate::SingletonTemplate<GameConfigManager> ConfigManager;
#define THE_CONFIGMANAGER ConfigManager::GetInstance()

#endif