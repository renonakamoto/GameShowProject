#include "PlayerWait.h"
#include "../Player.h"
#include "PlayerSprint.h"
#include "PlayerSquat.h"
#include "../../../../Engine/Input/InputManager.h"

void PlayerWait::Init(Player* player_)
{
	player_->SetIsSquad(false);
}

void PlayerWait::Update(Player* player_)
{
	// ˆÚ“®‚µ‚Ä‚¢‚½‚ç‘–‚éƒ‚[ƒVƒ‡ƒ“‚É‘JˆÚ
	if (player_->IsMove())
	{
		player_->ChangeState(PlayerSprint::GetInstance());
	}

	// C‚ª‰Ÿ‚³‚ê‚½‚ç‚½‚ç‚µ‚á‚ª‚Þƒ‚[ƒVƒ‡ƒ“‚É‘JˆÚ
	if (THE_INPUTMANAGER->GetKeyDown(KeyInfo::Key_C))
	{
		player_->ChangeState(PlayerSquat::GetInstance());
	}

	
	player_->Motion(PlayerMotionList::Wait);
}