#ifndef OBJECT_BASE_H_
#define OBJECT_BASE_H_

#include <string>

/**
* @brief オブジェクト基底クラス
*/
class ObjectBase
{
public:
	/**
	* @brief コンストラクタ
	*/
	ObjectBase():
		m_Tag("default")
	{}

	/**
	* @brief デストラクタ
	*/
	~ObjectBase(){}

	/**
	* @fn void Init()
	* @brief 初期化関数
	* @details 継承先で定義し、オブジェクトの初期化を行う
	*/
	virtual void Init()   = 0;

	/**
	* @fn void Update()
	* @brief 更新関数
	* @details 継承先で定義し、オブジェクトの更新を行う
	*/
	virtual void Update() = 0;

	/**
	* @fn void Draw()
	* @brief 描画関数
	* @details 継承先で定義し、オブジェクトの描画を行う
	*/
	virtual void Draw()   = 0;

	/**
	* @fn std::string GetTag()
	* @brief タグを返す関数関数
	* @return std::string タグ
	*/
	std::string GetTag() { return m_Tag; }

protected:
	/**
	* @fn void Release()
	* @brief 解放関数
	* @details 継承先で定義し、解放処理を行う
	*/
	virtual void Release() = 0;

protected:
	std::string m_Tag;	//! オブジェクトを識別するためのタグ
};

#endif