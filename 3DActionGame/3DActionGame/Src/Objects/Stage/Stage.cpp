#include "Stage.h"
#include "../../Utility/Vec2I.h"
#include "../../Utility/Calculation.h"

void Stage::Update()
{
}

void Stage::Draw()
{
	if (m_Model)m_Model->Render(DirectGraphics::GetInstance(), m_Pos, m_Scale, m_Rot);
}

float Stage::GetPolygonHeight(DirectX::XMFLOAT3 pos_)const
{
	UINT idx_x = static_cast<UINT>((pos_.x + StageWieth  / 2) / m_CellSize);
	UINT idx_y = static_cast<UINT>((pos_.z + StageHeight / 2) / m_CellSize);
	float height = -100.f;

	for (size_t v = 0; v < m_MapData[idx_y][idx_x].size(); v+=3)
	{
		DirectX::XMFLOAT3 vtx_a = m_MapData[idx_y][idx_x][v].Pos;
		DirectX::XMFLOAT3 vtx_b = m_MapData[idx_y][idx_x][v+1].Pos;
		DirectX::XMFLOAT3 vtx_c = m_MapData[idx_y][idx_x][v+2].Pos;

		// XZ平面で見た時に三角形のなかに入っているかを調べる
		DirectX::XMFLOAT2 a(vtx_a.x, vtx_a.z);
		DirectX::XMFLOAT2 b(vtx_b.x, vtx_b.z);
		DirectX::XMFLOAT2 c(vtx_c.x, vtx_c.z);
		DirectX::XMFLOAT2 p(pos_.x, pos_.z);
		// 三角形に点が含まれているか
		if (Calculation::HitTriangleAndPoint(a, b, c, p) == false) continue;

		// 含まれていた場合
		
		// ポリゴンの1頂点から法線を取得する
		DirectX::XMFLOAT3 n = m_MapData[idx_y][idx_x][v].Normal;

		// ポリゴンの高さを調べる
		height = (vtx_a.x * (1.f / n.y) * n.x) - (pos_.x * (1.f / n.y) * n.x) + (n.z * vtx_a.z * (1.f / n.y)) - (n.z * pos_.z * (1.f / n.y)) + vtx_a.y;
		break;
	}
	
	return height;
}

void Stage::Init()
{
	m_Model = ObjFileStrage::GetInstance()->GetModel("Stage");
	m_Tag = "stage";
	CreateSplitMapData();
}

void Stage::Release()
{
}

void Stage::CreateSplitMapData()
{
	// 分割した時の1マスのサイズを算出
	m_CellSize = StageWieth / StageSplitNum;
	// ステージのメッシュ情報を取得
	const std::vector<CVertex>* vertices = &m_Model->GetMeshData(0)->Vertices;
	
	for (size_t i = 0; i < vertices->size(); i += 3)
	{
		DirectX::XMFLOAT3 v[3];

		// ポリゴンの頂点座標を取得
		v[0] = vertices->at(i).Pos;
		v[1] = vertices->at(i+1).Pos;
		v[2] = vertices->at(i+2).Pos;

		// ステージの真ん中が原点になっているので左上原点にするために頂点座標をずらす
		for (int j = 0; j < 3; ++j)
		{
			v[j].x += (StageWieth  / 2);
			v[j].z += (StageHeight / 2);
		}
		
		// 分割するサイズで割って配列のサイズにする
		for (int j = 0; j < 3; ++j)
		{
			v[j] = DirectX::XMFLOAT3(v[j].x / m_CellSize, v[j].y, v[j].z / m_CellSize);
		}
		
		// 配列のどの要素にいれるかを算出	
		std::vector<Vec2I> add_index;	// 追加する要素番号を保存する変数
		for (int j = 0; j < 3; ++j)
		{
			bool can_add = true;
			Vec2I index(static_cast<int>(v[j].x), static_cast<int>(v[j].z));
			for (int k = 0; k < add_index.size(); ++k)
			{
				if (add_index[k] == index)
				{
					can_add = false;
					break;
				}
			}

			if (can_add)
			{
				add_index.push_back(index);
			}
		}

		for (size_t j = 0; j < add_index.size(); ++j)
		{
			m_MapData[add_index[j].Y][add_index[j].X].push_back(vertices->at(i));
			m_MapData[add_index[j].Y][add_index[j].X].push_back(vertices->at(i + 1));
			m_MapData[add_index[j].Y][add_index[j].X].push_back(vertices->at(i + 2));
		}
	}
}

