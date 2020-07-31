#ifndef THINKING_H_
#define THINKING_H_

#include "State.h"

class Thinking : public State
{
public:
	Thinking() {}
	virtual ~Thinking() {}

	void Update(Enemybase* enemy_) override;
};

#endif // !THINKING_H_
