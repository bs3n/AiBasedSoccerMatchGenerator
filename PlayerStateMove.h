#pragma once

#include "IPlayerState.h"
#include "Player.h"
#include "Pitch.h"

class PlayerStateMove :	public IPlayerState
{
public:
	
	void doAction(Player&, Pitch&, Ball&, Position&) override;

private:

};