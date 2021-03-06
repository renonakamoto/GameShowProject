#ifndef DIRECTGRAPHICS_H_
#define DIRECTGRAPHICS_H_

#include "../../Utility/SingletonTemplate.h"
#include "../Texture/Texture.h"
#include <d3dx9.h>
#include <Windows.h>

// 解放
#define	SAFE_DESTROY(x)	{ if(x) { (x)->Destroy(); (x) = NULL; } }

// 解放処理用のマクロを定義
#define SAFE_RELEASE(x) { if(x) { (x)->Release(); (x) = NULL; } }

/**
* @namespace MyDirectGraphics
* @brief DirectGraphics類をまとめた名前空間
*/
namespace MyDirectGraphics
{
	/**
	* @brief   DirectGraphicsを扱うクラス
	*/
	class DirectGraphics
	{

		friend MySingletonTemplate::SingletonTemplate<DirectGraphics>;
	public:
		/**
		* @brief グラフィックエンジンの初期化
		* @return bool 成功したかどうか
		* @details true->成功 | false->失敗
		* @details ゲームループ前に一度だけ実行する
		*/
		bool Init(HWND windowHandle_, int width_, int height_, bool isFullScreen_);

		/**
		* @brief 描画開始関数
		* @details 描画開始時に一度だけ呼び出す
		*/
		void StartDraw();

		/**
		* @brief 描画終了関数
		* @details 描画終了時に一度だけ呼び出す
		*/
		void EndDraw();

		/**
		* @brief デバイスを返す関数
		* @return LPDIRECT3DDEVICE9 グラフィックデバイス
		*/
		const LPDIRECT3DDEVICE9 GetD3DDevice() const { return m_pD3DDevice; }

		/**
		* @brief プレゼントパラメーターを返す関数
		* @return D3DPRESENT_PARAMETERS* プレゼントパラメーター
		*/
		const D3DPRESENT_PARAMETERS* GetD3DPresentParam() const { return m_pD3DPresentParam; }



	private:
		/**
		* @brief コンストラクタの簡単な説明
		*/
		DirectGraphics() :
			m_pD3DInterface(nullptr),
			m_pD3DDevice(nullptr),
			m_pD3DPresentParam(nullptr)
		{}

		/**
		* @brief デストラクタの簡単な説明
		*/
		~DirectGraphics() {}

		/**
		* @brief グラフィックインターフェースの作成
		* @return bool 成功したかどうか
		* @details true->成功 | false->失敗
		*/
		bool CreateGraphicsInterface();

		/**
		* @brief グラフィックデバイスの作成
		* @return bool 成功したかどうか
		* @details true->成功 | false->失敗
		*/
		bool CreateGraphicsDevice(HWND windowHandle_, int width_, int height_, bool isFullScreen_);

		/**
		* @brief ビューポートの設定
		* @return bool 成功したかどうか
		* @details true->成功 | false->失敗
		*/
		bool SetViewPort();


		LPDIRECT3D9			   m_pD3DInterface;			//! グラフィックインターフェース
		LPDIRECT3DDEVICE9	   m_pD3DDevice;			//! グラフィックデバイス
		D3DPRESENT_PARAMETERS* m_pD3DPresentParam;		//! プレゼントパラメータ
	};
}

typedef MySingletonTemplate::SingletonTemplate<MyDirectGraphics::DirectGraphics> DirectGraphics;
#define THE_GRAPHICS DirectGraphics::GetInstance()

#endif