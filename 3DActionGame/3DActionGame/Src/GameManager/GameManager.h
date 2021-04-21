#ifndef GAME_MANAGER_H_
#define GAME_MANAGER_H_

/**
* @brief ゲーム情報の管理を行うクラス
*/
class GameManager
{
public:
	/**
	* @fn static GameManager* GetInstance()
	* @brief インスタンスを返す関数
	* @return GameManager* インスタンスのポインタ
	*/
	static GameManager* GetInstance()
	{
		static GameManager instance;
		return &instance;
	}

	/**
	* @fn void GameClear()
	* @brief GameClearシーンの遷移する関数
	* @details ゲームクリアした際に呼ぶ
	*/
	void GameClear();

	/**
	* @fn void GameOver()
	* @brief GameOverシーンの遷移する関数
	* @details ゲームオーバーした際に呼ぶ
	*/
	void GameOver();

	/**
	* @fn void QuitGame()
	* @brief アプリケーションを終了する関数
	* @details アプリケーション終了フラグをオンにする
	*/
	void QuitGame() { m_Quit = true; }

	/**
	* @fn bool HasQuit()
	* @brief アプリケーション終了フラグを返す関数
	* @return bool アプリケーション終了フラグ
	*/
	bool HasQuit()const { return m_Quit; }
	
private:
	/**
	* @brief コンストラクタ
	*/
	GameManager():
		m_Quit(false)
	{}

	/**
	* @brief デストラクタ
	*/
	~GameManager()
	{}

private:
	bool m_Quit;	//! アプリケーションを終了したかどうか

};

#endif