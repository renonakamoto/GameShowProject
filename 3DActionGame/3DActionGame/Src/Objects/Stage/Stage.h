#ifndef STAGE_H_
#define STAGE_H_

#include "../../ObjectManager/Object3D.h"
#include "../../Model/ObjFileStrage.h"

class Stage : public Object3D
{
	static const int StageWieth = 1200;
	static const int StageHeight = 1200;
	static const int StageSplitNum = 10;

public:
	Stage() :
		m_Model(nullptr),
		m_CellSize(0)
	{
		m_Model = ObjFileStrage::GetInstance()->GetModel("Stage");
		if (m_Model)
		{
			CreateSplitMapData();
		}
	}

	~Stage()
	{
		Release();
	}


	void Init() override;
	void Update() override;
	void Draw() override;

	float GetPolygonHeight(DirectX::XMFLOAT3 pos_) const;

	std::vector<CVertex>* GetMapData() { return &m_MapData[0][1]; }

	bool IntersectRayAndMap(DirectX::XMFLOAT3 rayOrigin_, DirectX::XMFLOAT3 rayDistance_, float& height_);
	
private:
	void Release() override;
	void CreateSplitMapData();

private:
	std::vector<CVertex> m_MapData[StageSplitNum + 1][StageSplitNum + 1];
	float m_CellSize;

	ObjModel* m_Model;
};

#endif