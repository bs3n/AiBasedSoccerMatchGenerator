#pragma once

#include "PlayerStateMove.h"
#include "Player.h"
#include "Ball.h"
#include "Position.h"
#include "FiniteStateMachine.h"
#include "Match.h"

PlayerStateMove::PlayerStateMove()
{
}

PlayerStateMove::~PlayerStateMove()
{
}

void PlayerStateMove::doAction(Player& player, Pitch& pitch, Ball& ball)
{
	beginTurn(player, pitch);

	player.setTarget(*ball.getPosition());
	player.move(*player.getTarget());

	int playerPosX = player.getPosition()->getX();
	int playerPosY = player.getPosition()->getY();
	Position ballPos = *ball.getPosition();

	if (playerPosX == ballPos.getX() && playerPosY == ballPos.getY())
	{
		if (pitch.getTile(playerPosX, playerPosY)->getPlayers()->size() > 0)
		{
			if (!player.hasBall())
			{
				player.setState(State::Interact);
				player.setTarget(ballPos);
			}
	}
		else
		{
			processText(player.getName() + " holt sich den freien Ball.\n\n");
			pause(Match::textSpeed);

			player.hasBall(true);
			player.setState(State::Attack);
			player.setTarget(*player.getOpponentGoalPosition());
		}
	}

	endTurn(player, pitch);
}