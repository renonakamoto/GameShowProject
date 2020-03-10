#ifndef DIRECTGRAPHICS_H_
#define DIRECTGRAPHICS_H_

#include "../../Utility/SingletonTemplate.h"
#include <d3dx9.h>
#include <Windows.h>

/**
* @namespace MyDirectGraphics
* @brief DirectGraphics類をまとめた名前空間
*/
namespace MyDirectGraphics
{
	/**
	* @brief 簡単なクラスの説明
	* @details 詳細なクラスの説明
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
		bool Init(HWND windowHandle_, bool isFullScreen_);

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
		//~DirectGraphics() {}

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
		bool CreateGraphicsDevice(HWND windowHandle_, bool isFullScreen_);

		/**
		* @brief ビューポートの設定
		* @return bool 成功したかどうか
		* @details true->成功 | false->失敗
		*/
		bool SetViewPort();

		//! ほにゃららで使う変数
		LPDIRECT3D9			   m_pD3DInterface;
		//! ほにゃららで使う変数
		LPDIRECT3DDEVICE9	   m_pD3DDevice;
		//! ほにゃららで使う変数
		D3DPRESENT_PARAMETERS* m_pD3DPresentParam;
	};
}

#endif