#ifndef MODEL_H_
#define MODEL_H_

#include "../../Utility/GraphicsUtility.h"

/**
* @brief モデルデータの基底クラス
*/
class Model
{
public:
	/**
	* @brief コンストラクタ
	*/
	Model()
	{}

	/**
	* @brief デストラクタ
	*/
	virtual ~Model()
	{
		m_MeshList.clear();
	}
	
	/**
	* @fn std::vector<MeshData>* GetMeshData()
	* @brief モデルのデータを返す関数
	* @return std::vector<MeshData>* メッシュデータのポインタ
	*/
	std::vector<MeshData>* GetMeshData() { return &m_MeshList; }

protected:
	std::vector<MeshData> m_MeshList;	//! メッシュリスト
	
};

#endif