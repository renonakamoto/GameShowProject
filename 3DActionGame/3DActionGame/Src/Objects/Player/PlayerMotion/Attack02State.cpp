#include "Attack02State.h"
#include "../Player.h"

PlayerState* Attack02State::CheckState(Player* player_)
{
	return nullptr;
}

void Attack02State::Update(Player* player_)
{
}

void Attack02State::Enter(Player* player_)
{
	player_->SetMotion("Attack02");
}
