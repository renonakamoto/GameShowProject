#ifndef MODEL_H_
#define MODEL_H_

#include "../Utility/GraphicsUtility.h"

class Model
{
public:
	Model()
	{}

	~Model(){}

	size_t GetMeshNum() const { return m_MeshList.size(); }

	const MeshData* GetMeshData(UINT idx_) const {
		// 配列の要素数以上なら存在しないのでnullptrを返す
		if (idx_ >= m_MeshList.size()) return nullptr;
		&m_MeshList[idx_];
	}

protected:
	std::vector<MeshData> m_MeshList;	//! メッシュリスト
	
};

#endif