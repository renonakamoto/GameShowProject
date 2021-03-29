#ifndef PLAYER_STATE_H_
#define PLAYER_STATE_H_

class Player;

class PlayerState
{
public:
	PlayerState()
	{}

	~PlayerState()
	{}

	virtual PlayerState* CheckState(Player* player_) = 0;
	virtual void Update(Player* player_) = 0;

	virtual void Enter(Player* player_) = 0;

private:
	

};

#endif