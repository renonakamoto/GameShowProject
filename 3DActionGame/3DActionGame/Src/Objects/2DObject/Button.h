#ifndef BUTTON_H_
#define BUTTON_H_

#include <string>
#include "../../ObjectManager/Object2D.h"
#include "../../CollisionManager/Shape/2D/Rect/Rect.h"
#include "../../Engine/Engine.h"
#include "../../Utility/Calculation.h"

/**
* @brief ボタンクラス
*/
template<class T>
class Button : public Object2D
{
public:
	/**
	* @brief コンストラクタ
	* @param[in] normal_  マウスと重なっていない時のテクスチャキーワード
	* @param[in] hover_ マウスと重なっている時のテクスチャキーワード
	* @param[in] fp_ 押したときに呼ばれるコールバック関数
	* @param[in] pos_ 描画座標 (左上原点)
	*/
	Button(std::string normal_, std::string hover_, DirectX::XMFLOAT3 pos_, T* t_, void(T::* fp_)(void)) :
		Object2D(pos_),
		m_Normal(normal_), 
		m_Hover(hover_),
		m_PushedFunc(fp_),
		m_Receiver(t_),
		m_IsHover(false)
	{		
		TextureData* tex = TEX_MANAGER->GetTexture(normal_);
		if (tex)
		{
			m_Rect.m_Top	= m_Pos.y;
			m_Rect.m_Bottom = m_Pos.y + tex->Height;
			m_Rect.m_Left	= m_Pos.x;
			m_Rect.m_Right	= m_Pos.x + tex->Width;
		}
	}

	/**
	* @brief デストラクタ
	*/
	~Button()
	{}

	/**
	* @fn void Init()
	* @brief 初期化関数
	*/
	void Init()override
	{}

	/**
	* @fn void Update()
	* @brief 更新関数
	* @details ゲームループで1フレームに一度呼ばれる
	*/
	void Update()override;

	/**
	* @fn void Draw()
	* @brief 描画関数
	* @details ゲームループで1フレームに一度呼ばれる
	*/
	void Draw()override;

private:
	/**
	* @fn void Release()
	* @brief 解放関数
	*/
	void Release()override
	{}
	

private:
	std::string m_Normal;		//! マウスと重なっていない時のテクスチャキーワード
	std::string m_Hover;		//! マウスと重なっている時のテクスチャキーワード
	Rect		m_Rect;			//! ボタンの矩形情報
	bool		m_IsHover;		//! マウスと重なっているかどうかを保存する変数
	T*			m_Receiver;		//! 
	void (T::*m_PushedFunc)(void);	//! 押されたときに呼び出す関数を保存する変数
};

#endif

template<class T>
inline void Button<T>::Update()
{
	POINT mouse_pos = INPUT->GetMousePos();
	m_IsHover = Calculation::HitRectAndPoint(m_Rect, static_cast<float>(mouse_pos.x), static_cast<float>(mouse_pos.y));

	if (m_IsHover && INPUT->GetMouseDown(MouseButton::Left))
	{
		(m_Receiver->*m_PushedFunc)();
	}
}

template<class T>
inline void Button<T>::Draw()
{
	GRAPHICS->SetRasterizerMode(RasterizerMode::MODE_CULL_BACK);
	if (m_IsHover)
	{
		TEX_MANAGER->Render(m_Hover, m_Pos);
	}
	else
	{
		TEX_MANAGER->Render(m_Normal, m_Pos);
	}
}