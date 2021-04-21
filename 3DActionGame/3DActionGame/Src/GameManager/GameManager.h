#ifndef GAME_MANAGER_H_
#define GAME_MANAGER_H_

/**
* @brief ゲーム情報の管理を行うクラス
*/
class GameManager
{
public:
	static GameManager* GetInstance()
	{
		static GameManager instance;
		return &instance;
	}

	void QuitGame() { m_Quit = true; }
	
	bool HasQuit()const { return m_Quit; }

private:
	GameManager():
		m_Quit(false)
	{}

	~GameManager()
	{}

private:
	bool m_Quit;	//! ゲームが終了したかどうか

};

#endif