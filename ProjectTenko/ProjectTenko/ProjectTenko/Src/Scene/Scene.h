#ifndef SCENE_H_
#define SCENE_H_

#include <Windows.h>
#include "SceneDefinition.h"
#include "SceneChanger.h"

class Scene
{
public:
	/**
	* @biref コンストラクタ
	* @param[in] sceneChanger_ シーン変更のためのインターフェイス(SceneManager)のポインタ
	*/
	Scene(SceneChanger* sceneChanger_) :
		m_SceneChanger(sceneChanger_),
		m_CurrentState(SceneState::Init),
		m_ThreadHandle(nullptr),
		m_dwThreadID(0)
	{	}

	/**
	* @biref デストラクタ
	*/
	virtual ~Scene() {	}

	/**
	* @biref 更新関数
	*/
	virtual void Update() = 0;

	/**
	* @biref 描画関数
	*/
	virtual void Draw() {	};
	
protected:

	/**
	* @biref Main処理関数
	*/
	virtual void Main() = 0;

	/**
	* @brief Loading処理関数
	*/
	virtual void Load() = 0;

	virtual DWORD WINAPI LoadResources(LPVOID lpParam_) = 0;

protected:
	SceneChanger* m_SceneChanger;	//!< シーン変更のためのインターフェイスを保持するポインタ
	SceneState m_CurrentState;		//!< 現在のシーンの状態
	HANDLE m_ThreadHandle;			//!< マルチスレッド用のハンドル保存変数
	DWORD m_dwThreadID;				//!< マルチスレッド用のスレッドID
};

#endif // !SCENE_H_