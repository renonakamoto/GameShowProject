#include "PlayerEffect.h"
#include "../../../Engine/Texture/Texture.h"

PlayerEffect::PlayerEffect()
{
	m_TextureTable[std::make_pair(PlayerEffectType::PlyaerChase, 0)] = "assets/effect/chaseeffect/chase_effect1.png";
	m_TextureTable[std::make_pair(PlayerEffectType::PlyaerChase, 1)] = "assets/effect/chaseeffect/chase_effect2.png";
	m_TextureTable[std::make_pair(PlayerEffectType::PlyaerChase, 2)] = "assets/effect/chaseeffect/chase_effect3.png";
	m_TextureTable[std::make_pair(PlayerEffectType::PlyaerChase, 3)] = "assets/effect/chaseeffect/chase_effect4.png";
	m_TextureTable[std::make_pair(PlayerEffectType::PlyaerChase, 4)] = "assets/effect/chaseeffect/chase_effect5.png";

	m_TextureTable[std::make_pair(PlayerEffectType::PlayerSneak, 0)] = "assets/effect/sneakeffect/sneak_effect1.png";
	m_TextureTable[std::make_pair(PlayerEffectType::PlayerSneak, 1)] = "assets/effect/sneakeffect/sneak_effect2.png";
	m_TextureTable[std::make_pair(PlayerEffectType::PlayerSneak, 2)] = "assets/effect/sneakeffect/sneak_effect3.png";
	m_TextureTable[std::make_pair(PlayerEffectType::PlayerSneak, 3)] = "assets/effect/sneakeffect/sneak_effect4.png";
	m_TextureTable[std::make_pair(PlayerEffectType::PlayerSneak, 4)] = "assets/effect/sneakeffect/sneak_effect5.png";

	for (int i = 0; i < 5; ++i)
	{
		THE_TEXTUREMANAGER->Load(m_TextureTable[std::make_pair(PlayerEffectType::PlyaerChase, i)]);
	}

	for (int i = 0; i < 5; ++i)
	{
		THE_TEXTUREMANAGER->Load(m_TextureTable[std::make_pair(PlayerEffectType::PlayerSneak , i)]);
	}

	m_PlayerEffect[(int)PlayerEffectType::PlyaerChase].CurrentNum	  = 0;
	m_PlayerEffect[(int)PlayerEffectType::PlyaerChase].ChangeFlameNum = 10;
	m_PlayerEffect[(int)PlayerEffectType::PlyaerChase].MaxNum		  = 5;
	m_PlayerEffect[(int)PlayerEffectType::PlyaerChase].PlayerFrame	  = 0;
	
	m_PlayerEffect[(int)PlayerEffectType::PlayerSneak].CurrentNum     = 0;
	m_PlayerEffect[(int)PlayerEffectType::PlayerSneak].ChangeFlameNum = 10;
	m_PlayerEffect[(int)PlayerEffectType::PlayerSneak].MaxNum	      = 5;
	m_PlayerEffect[(int)PlayerEffectType::PlayerSneak].PlayerFrame    = 0;
		
}

PlayerEffect::~PlayerEffect()
{
}

void PlayerEffect::InitEffect(PlayerEffectType type_)
{
	m_PlayerEffect[(int)type_].CurrentNum		= 0;
	m_PlayerEffect[(int)type_].ChangeFlameNum	= 10;
	m_PlayerEffect[(int)type_].MaxNum			= 5;
	m_PlayerEffect[(int)type_].PlayerFrame		= 0;
}

void PlayerEffect::Update(PlayerEffectType type_)
{
	if (type_ == PlayerEffectType::Non) return;

	// エフェクトのフレームを進める
	m_PlayerEffect[(int)type_].PlayerFrame++;
	int player_frame = m_PlayerEffect[(int)type_].PlayerFrame;
	int change_frame = m_PlayerEffect[(int)type_].ChangeFlameNum;

	// チェンジするフレームになったら
	if (player_frame >= change_frame)
	{
		// フレームをリセット
		m_PlayerEffect[(int)type_].PlayerFrame = 0;
		// エフェクトチェンジ
		m_PlayerEffect[(int)type_].CurrentNum++;
		
		// もし最後のエフェクトになったら
		int current_num = m_PlayerEffect[(int)type_].CurrentNum;
		int max_num		= m_PlayerEffect[(int)type_].MaxNum;
		if (current_num >= max_num)
		{
			// 最初のエフェクトに戻す
			m_PlayerEffect[(int)type_].CurrentNum = 0;
		}
	}
}

void PlayerEffect::Draw(PlayerEffectType type_)
{
	if (type_ == PlayerEffectType::Non) return;

	int current_num = m_PlayerEffect[(int)type_].CurrentNum;
	THE_TEXTUREMANAGER->DrawTexture(0.0f, 0.0f, m_TextureTable[std::make_pair(type_, current_num)]);
}
