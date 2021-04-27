#include "Stage.h"
#include "../../Utility/Vec2I.h"
#include "../../Utility/Calculation.h"
#include "../../Engine/Engine.h"

void Stage::Draw()
{
	DirectGraphics* graphics = GRAPHICS;
	ID3D11DeviceContext* context = GRAPHICS->GetContext();

	// ラスタラスザの設定
	graphics->SetRasterizerMode(RasterizerMode::MODE_CULL_NONE);
	// 頂点シェーダの設定
	context->VSSetShader(graphics->GetSimpleVertexShader()->GetShaderInterface(), NULL, 0U);
	// ピクセルシェーダの設定
	context->PSSetShader(graphics->GetPixelShader()->GetShaderInterface(), NULL, 0U);

	ID3D11ShaderResourceView* depth_tex = graphics->GetDepthTextureView();
	context->PSSetShaderResources(1U, 1U, &depth_tex);

	ID3D11SamplerState* sampler_state = graphics->GetShadowMapSamplerState();
	context->PSSetSamplers(1U, 1U, &sampler_state);

	if (m_Model)m_Model->Render(m_Pos, m_Scale, m_Rot);
}

void Stage::DrawShadowMap()
{
	if (m_Model == nullptr) return;

	DirectGraphics* graphics = GRAPHICS;
	ID3D11DeviceContext* context = GRAPHICS->GetContext();

	// ラスタラスザの設定
	graphics->SetRasterizerMode(RasterizerMode::MODE_CULL_NONE);
	// 頂点シェーダの設定
	context->VSSetShader(graphics->GetDepthVertexShader()->GetShaderInterface(), NULL, 0U);
	// ピクセルシェーダの設定
	context->PSSetShader(graphics->GetDepthPixelShader()->GetShaderInterface(), NULL, 0U);
	
	m_Model->Render(m_Pos, m_Scale, m_Rot);
}

float Stage::GetPolygonHeight(DirectX::XMFLOAT3 pos_)const
{
	// ステージ外なら
	if (m_Pos.x > (STAGE_WIETH / 2) || m_Pos.x <  -(STAGE_WIETH / 2) ||
		m_Pos.z > (STAGE_HEIGHT / 2)  || m_Pos.z < -(STAGE_HEIGHT / 2))
	{
		return -100.f;
	}

	UINT idx_x = static_cast<UINT>((pos_.x + STAGE_WIETH / 2) / m_CellSize);
	UINT idx_y = static_cast<UINT>((pos_.z + STAGE_HEIGHT / 2) / m_CellSize);
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

bool Stage::IntersectRayAndStage(DirectX::XMFLOAT3 rayOrigin_, DirectX::XMFLOAT3 rayDistance_, float& height_)
{
	// レイの終点のインデックスを算出
	Vec2I re_idx;
	DirectX::XMFLOAT3 ray_end = Calculation::Add(rayOrigin_, rayDistance_);
	re_idx.X = static_cast<UINT>((ray_end.x + STAGE_WIETH / 2) / m_CellSize);
	re_idx.Y = static_cast<UINT>((ray_end.z + STAGE_HEIGHT / 2) / m_CellSize);

	for (size_t v = 0; v < m_MapData[re_idx.Y][re_idx.X].size(); v += 3)
	{
		// ポリゴン
		DirectX::XMFLOAT3 vtx_a = m_MapData[re_idx.Y][re_idx.X][v].Pos;
		DirectX::XMFLOAT3 vtx_b = m_MapData[re_idx.Y][re_idx.X][v + 1].Pos;
		DirectX::XMFLOAT3 vtx_c = m_MapData[re_idx.Y][re_idx.X][v + 2].Pos;
		
		// XZ平面で見た時に三角形のなかに入っているかを調べる
		DirectX::XMFLOAT2 a(vtx_a.x, vtx_a.z);
		DirectX::XMFLOAT2 b(vtx_b.x, vtx_b.z);
		DirectX::XMFLOAT2 c(vtx_c.x, vtx_c.z);
		DirectX::XMFLOAT2 p(ray_end.x, ray_end.z);
		// 三角形に点が含まれているか
		if (Calculation::HitTriangleAndPoint(a, b, c, p) == false) continue;

		// ポリゴンと線分の当たり判定
		DirectX::XMFLOAT3 intersect_pos;
		if (Calculation::IntersectRayAndTriangle(rayOrigin_, rayDistance_, vtx_a, vtx_b, vtx_c, intersect_pos) == true)
		{
			// ポリゴンの1頂点から法線を取得する
			DirectX::XMFLOAT3 n = m_MapData[re_idx.Y][re_idx.X][v].Normal;
			height_ = (vtx_a.x * (1.f / n.y) * n.x) - (ray_end.x * (1.f / n.y) * n.x) + (n.z * vtx_a.z * (1.f / n.y)) - (n.z * ray_end.z * (1.f / n.y)) + vtx_a.y;
			return true;
		}
		else {
			return false;
		}
	}

	return false;
}

void Stage::CreateSplitMapData()
{
	// 分割した時の1マスのサイズを算出
	m_CellSize = STAGE_WIETH / STAGE_SPLITNUM;
	// ステージのメッシュ情報を取得
	const std::vector<MeshData>* mesh    = m_Model->GetMeshData();
	const std::vector<CVertex>* vertices = &mesh->at(0).Vertices;
	
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
			v[j].x += (STAGE_WIETH / 2);
			v[j].z += (STAGE_HEIGHT / 2);
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

