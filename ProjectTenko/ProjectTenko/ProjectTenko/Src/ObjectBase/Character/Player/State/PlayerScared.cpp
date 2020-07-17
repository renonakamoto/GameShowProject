#include "PlayerScared.h"
#include "../Player.h"

void PlayerScared::Init(Player* player_)
{
	player_->SetIsSquad(false);
}

void PlayerScared::Update(Player* player_)
{
	player_->Motion(PlayerMotionList::Scared);
}
