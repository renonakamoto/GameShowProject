#ifndef OBJECT_MANAGER_H_
#define OBJECT_MANAGER_H_

#include <vector>
#include "ObjectBase.h"
#include "ShadowMapObject.h"

/**
* @brief ゲームオブジェクトを管理するクラス
*/
class ObjectManager
{
public:
	/**
	* @fn static ObjectManager* GetInstance()
	* @brief インスタンスを返す関数
	* @return ObjectManager* インスタンスのポインタ
	*/
	static ObjectManager* GetInstance()
	{
		static ObjectManager instance;
		return &instance;
	}

	/**
	* @fn void Init()
	* @brief リストに登録されているゲームオブジェクトのInit関数を呼ぶ関数
	*/
	void Init();

	/**
	* @fn void Update()
	* @brief リストに登録されているゲームオブジェクトのUpdate関数を呼ぶ関数
	*/
	void Update();

	/**
	* @fn void Draw()
	* @brief リストに登録されているゲームオブジェクトのDraw関数を呼ぶ関数
	*/
	void Draw();

	void DrawShadowMapObj();

	/**
	* @fn void Register(Object3D* object_)
	* @brief オブジェクトリストに追加する関数
	* @param[in] object_ ゲームオブジェクト
	*/
	void Register(ObjectBase* object_);

	void ResisterShadowMap(ShadowMapObject* object_);

	/**
	* @fn void Release(Object3D* object_)
	* @brief リストから指定したオブジェクトを削除する関数
	* @param[in] object_ 削除したいオブジェクト
	* @details 確保されているメモリも一緒に解放する
	*/
	void Release(ObjectBase* object_);

	void Release(ShadowMapObject* object_);

	/**
	* @fn void AllRelease()
	* @brief リストに登録されているオブジェクトをすべて削除する関数
	* @details 確保されているメモリも一緒に解放する
	*/
	void AllRelease();

	/**
	* @fn ObjectBase* GetObj(std::string tag_)
	* @brief 指定されたタグのついているオブジェクトのポインタを返す関数
	* @return ObjectBase* オブジェクトのポインタ、見つからなかったらnullptrを返す
	* @details 見つけた最初のオブジェクトを返す
	*/
	ObjectBase* GetObj(std::string tag_);

private:
	/**
	* @brief コンストラクタ
	*/
	ObjectManager()
	{}

	/**
	* @brief デストラクタ
	*/
	~ObjectManager()
	{
		AllRelease();
	}

private:
	std::vector<ObjectBase*> m_ObjectList;	//! ゲームオブジェクトリスト
	std::vector<ShadowMapObject*> m_ShadowMapObject;
	
};

#endif