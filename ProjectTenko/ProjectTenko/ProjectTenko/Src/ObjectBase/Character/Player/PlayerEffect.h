#ifndef PLAYEREFFECT_H_
#define PLAYEREFFECT_H_

#include <string>
#include <vector>
#include <map>

enum class PlayerEffectType
{
	PlyaerChase,
	PlayerSneak,

	MaxPlayerEffectType,

	Non,
};

class PlayerEffect
{
	struct PlayerEffectData
	{
		int  PlayerFrame;
		int  CurrentNum;
		int  MaxNum;
		int  ChangeFlameNum;
	};

public:
	PlayerEffect();
	~PlayerEffect();
	
	void InitEffect(PlayerEffectType type_);

	void Update(PlayerEffectType type_);

	void Draw(PlayerEffectType type_);

private:
	
	PlayerEffectData m_PlayerEffect[(int)PlayerEffectType::MaxPlayerEffectType];
	
	std::map<std::pair<PlayerEffectType, int>, std::string> m_TextureTable;
};

#endif