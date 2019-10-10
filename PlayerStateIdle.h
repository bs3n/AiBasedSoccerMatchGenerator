#pragma once

#include "PlayerState.h"

class Player;
class Pitch;
class Ball;

class PlayerStateIdle :	public PlayerState
{
public:

	PlayerStateIdle();
	~PlayerStateIdle();

	void doAction(Player&, Pitch&, Ball&) override;
};