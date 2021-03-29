#include "Attack01State.h"
#include "../Player.h"

PlayerState* Attack01State::CheckState(Player* player_)
{
	return nullptr;
}

void Attack01State::Update(Player* player_)
{
}

void Attack01State::Enter(Player* player_)
{
	player_->SetMotion("Attack01");
}
