#include "PlayerEffect.h"
#include "../../../Engine/Texture/Texture.h"

int Scast(PlayerEffectType param_) { return static_cast<int>(param_); }

PlayerEffect::PlayerEffect()
{
	m_TextureKeyTable[std::make_pair(PlayerEffectType::PlyaerChase, 0)] = "assets/effect/chaseeffect/chase_effect1.png";
	m_TextureKeyTable[std::make_pair(PlayerEffectType::PlyaerChase, 1)] = "assets/effect/chaseeffect/chase_effect2.png";
	m_TextureKeyTable[std::make_pair(PlayerEffectType::PlyaerChase, 2)] = "assets/effect/chaseeffect/chase_effect3.png";
	m_TextureKeyTable[std::make_pair(PlayerEffectType::PlyaerChase, 3)] = "assets/effect/chaseeffect/chase_effect4.png";
	m_TextureKeyTable[std::make_pair(PlayerEffectType::PlyaerChase, 4)] = "assets/effect/chaseeffect/chase_effect5.png";

	m_TextureKeyTable[std::make_pair(PlayerEffectType::PlayerSneak, 0)] = "assets/effect/sneakeffect/sneak_effect1.png";
	m_TextureKeyTable[std::make_pair(PlayerEffectType::PlayerSneak, 1)] = "assets/effect/sneakeffect/sneak_effect2.png";
	m_TextureKeyTable[std::make_pair(PlayerEffectType::PlayerSneak, 2)] = "assets/effect/sneakeffect/sneak_effect3.png";
	m_TextureKeyTable[std::make_pair(PlayerEffectType::PlayerSneak, 3)] = "assets/effect/sneakeffect/sneak_effect4.png";
	m_TextureKeyTable[std::make_pair(PlayerEffectType::PlayerSneak, 4)] = "assets/effect/sneakeffect/sneak_effect5.png";

	for (int i = 0; i < 5; ++i)
	{
		THE_TEXTUREMANAGER->Load(m_TextureKeyTable[std::make_pair(PlayerEffectType::PlyaerChase, i)]);
	}

	for (int i = 0; i < 5; ++i)
	{
		THE_TEXTUREMANAGER->Load(m_TextureKeyTable[std::make_pair(PlayerEffectType::PlayerSneak , i)]);
	}

	m_PlayerEffect[Scast(PlayerEffectType::PlyaerChase)].CurrentNum		= 0;
	m_PlayerEffect[Scast(PlayerEffectType::PlyaerChase)].ChangeFlameNum	= 10;
	m_PlayerEffect[Scast(PlayerEffectType::PlyaerChase)].MaxNum			= 5;
	m_PlayerEffect[Scast(PlayerEffectType::PlyaerChase)].CurrentFrameNum	= 0;
	
	m_PlayerEffect[Scast(PlayerEffectType::PlayerSneak)].CurrentNum		= 0;
	m_PlayerEffect[Scast(PlayerEffectType::PlayerSneak)].ChangeFlameNum	= 10;
	m_PlayerEffect[Scast(PlayerEffectType::PlayerSneak)].MaxNum			= 5;
	m_PlayerEffect[Scast(PlayerEffectType::PlayerSneak)].CurrentFrameNum	= 0;
		
}

PlayerEffect::~PlayerEffect()
{
	for (int i = 0; i < 5; ++i)
	{
		THE_TEXTUREMANAGER->Release(m_TextureKeyTable[std::make_pair(PlayerEffectType::PlyaerChase, i)]);
	}

	for (int i = 0; i < 5; ++i)
	{
		THE_TEXTUREMANAGER->Release(m_TextureKeyTable[std::make_pair(PlayerEffectType::PlayerSneak, i)]);
	}
}

void PlayerEffect::InitEffect(PlayerEffectType type_)
{
	m_PlayerEffect[Scast(type_)].CurrentNum		  = 0;
	m_PlayerEffect[Scast(type_)].ChangeFlameNum	  = 10;
	m_PlayerEffect[Scast(type_)].MaxNum			  = 5;
	m_PlayerEffect[Scast(type_)].CurrentFrameNum  = 0;
}

void PlayerEffect::Update(PlayerEffectType type_)
{
	if (type_ == PlayerEffectType::Non) return;

	// エフェクトのフレームを進める
	m_PlayerEffect[Scast(type_)].CurrentFrameNum++;
	int player_frame = m_PlayerEffect[Scast(type_)].CurrentFrameNum;
	int change_frame = m_PlayerEffect[Scast(type_)].ChangeFlameNum;

	// チェンジするフレームになったら
	if (player_frame >= change_frame)
	{
		// フレームをリセット
		m_PlayerEffect[Scast(type_)].CurrentFrameNum = 0;
		// エフェクトチェンジ
		m_PlayerEffect[Scast(type_)].CurrentNum++;
		
		// もし最後のエフェクトになったら
		int current_num = m_PlayerEffect[Scast(type_)].CurrentNum;
		int max_num		= m_PlayerEffect[Scast(type_)].MaxNum;
		if (current_num >= max_num)
		{
			// 最初のエフェクトに戻す
			m_PlayerEffect[Scast(type_)].CurrentNum = 0;
		}
	}
}

void PlayerEffect::Draw(PlayerEffectType type_)
{
	if (type_ == PlayerEffectType::Non) return;

	int current_num = m_PlayerEffect[Scast(type_)].CurrentNum;
	THE_TEXTUREMANAGER->DrawTexture(0.0f, 0.0f, m_TextureKeyTable[std::make_pair(type_, current_num)]);
}
