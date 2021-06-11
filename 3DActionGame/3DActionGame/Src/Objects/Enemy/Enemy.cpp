#include "Enemy.h"
#include "../../ObjectManager/ObjectManager.h"
#include "../../CollisionManager/CollisionManager.h"
#include "../../CollisionManager/Shape/3D/OBB/ShapeOBB.h"
#include "../../Engine/Engine.h"

void Enemy::Update()
{
	// 状態のチェックを行う
	EnemyState* state = m_State->CheckState(this);

	// 前のフレームの状態と違った場合は更新する
	if (state != m_State)
	{
		m_State = state;
		m_State->Enter(this);
	}
	
	// ステートの更新
	m_State->Update(this);
	
	// モーションのフレームを進める
	m_Model->Animate();
}

void Enemy::Draw()
{
	if (!m_Model) return;

	DirectGraphics* graphics = GRAPHICS;
	ID3D11DeviceContext* context = GRAPHICS->GetContext();

	// ラスタラスザの設定
	graphics->SetRasterizerMode(RasterizerMode::MODE_CULL_NONE);
	// 頂点シェーダの設定
	context->VSSetShader(graphics->GetVertexShader()->GetShaderInterface(), nullptr, 0U);
	// ピクセルシェーダの設定
	context->PSSetShader(graphics->GetPixelShader()->GetShaderInterface(), nullptr, 0U);

	ID3D11ShaderResourceView* depth_tex = graphics->GetDepthTextureView();
	context->PSSetShaderResources(1U, 1U, &depth_tex);
	ID3D11SamplerState* sampler_state = graphics->GetShadowMapSamplerState();
	context->PSSetSamplers(1U, 1U, &sampler_state);

	ID3D11ShaderResourceView* normal_tex = TEX_MANAGER->GetTexture("GrenadierNormalTex")->Texture.Get();
	context->PSSetShaderResources(2U, 1U, &depth_tex);

	m_Model->Render( m_Pos, m_Scale, m_Rot);

	context->VSSetShader(nullptr, nullptr, 0U);
	context->PSSetShader(nullptr, nullptr, 0U);
	ID3D11ShaderResourceView* nullSRV[1] = { nullptr };
	context->PSSetShaderResources(2U, 1U, nullSRV);

}

void Enemy::DrawShadowMap()
{
	if (!m_Model) return;

	DirectGraphics* graphics = GRAPHICS;
	ID3D11DeviceContext* context = GRAPHICS->GetContext();

	// ラスタラスザの設定
	graphics->SetRasterizerMode(RasterizerMode::MODE_CULL_NONE);
	// 頂点シェーダの設定
	context->VSSetShader(graphics->GetDepthSkinningVertexShader()->GetShaderInterface(), NULL, 0U);
	// ピクセルシェーダの設定
	context->PSSetShader(graphics->GetDepthPixelShader()->GetShaderInterface(), NULL, 0U);

	m_Model->Render(m_Pos, m_Scale, m_Rot);
}

void Enemy::Damage(int damageNum_)
{
	m_Hp -= damageNum_;

	m_IsHit = true;
}

void Enemy::Init()
{
	// モデル情報の取得
	m_Model = std::make_unique<SkeletalModel>(FbxStorage::GetInstance()->GetModel("Enemy"));
	
	// ステートの初期化
	m_State = EnemyIdleState::GetInstance();
	m_State->Enter(this);

	// 参照用のステージを取得
	ObjectBase* stage = ObjectManager::GetInstance()->GetObj("Stage");
	if (stage) m_Stage = dynamic_cast<Stage*>(stage);
	if (m_Stage)
	{
		m_Pos.y = m_Stage->GetPolygonHeight(m_Pos);
	}

	// 当たり判定用OBBの初期化
	DirectX::XMFLOAT3 shape_pos = m_Pos;
	shape_pos.y = m_Pos.y + m_EnemySize.y / 2;
	m_Shape = std::make_shared<ShapeOBB>(shape_pos, m_EnemySize.x / 2, m_EnemySize.y / 2, m_EnemySize.z / 2);
	
	// コリジョンマネージャーに登録
	CollisionManager::GetInstance()->Register(this);
}

void Enemy::Release()
{
	CollisionManager::GetInstance()->Release(this);	
}