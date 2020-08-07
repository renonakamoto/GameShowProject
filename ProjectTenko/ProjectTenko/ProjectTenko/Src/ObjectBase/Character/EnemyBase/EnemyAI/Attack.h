#include "State.h"

class Attack : public State
{
public:
	Attack() {}
	virtual ~Attack() {}

	void Update(Enemybase* enemy_) override
	{
		enemy_->Attack();
	}
};