#include "PlayerStateDefend.h"
#include "Match.h"

void PlayerStateDefend::doAction(Player& player, Pitch& pitch, Ball& ball)
{
	beginTurn(player, pitch);

	int rndPlayer = rand() % (10 / player.getLevel()) + 1;

	auto playerList = *pitch.getPlayersOnTiles(player.getPosition()->getX(), player.getPosition()->getY());

	for (auto opponent : playerList)
	{
		if (!opponent->hasBall())
		{
			continue;
		}

		if (player.getOpponentGoalPosition()->getX() == opponent->getOpponentGoalPosition()->getX())
		{
			if (player.getLevel() > opponent->getLevel())
			{
				string text = opponent->getName() + " passt den Ball zu " + player.getName() + "\n\n";
				std::cout << text;
				Match::addTextOutput(text);
				std::this_thread::sleep_for(std::chrono::milliseconds(Match::textSpeed));

				player.hasBall(true);
				player.setState(State::Attack);
				player.setTarget(*player.getOpponentGoalPosition());

				opponent->hasBall(false);
				opponent->setState(State::Idle);
				opponent->setTarget(Position(0, 0));
			}
			break;
		}

		string text = player.getName() + " geht in einen Zweikampf mit " + opponent->getName();
		std::cout << text;
		Match::addTextOutput(text);
		std::this_thread::sleep_for(std::chrono::milliseconds(Match::textSpeed * 2));

		int rndOpponent = rand() % (opponent->getLevel()) + 1;

		if (rndPlayer >= rndOpponent)
		{
			text = " und nimmt ihm den Ball ab.\n\n";
			std::cout << text;
			Match::addTextOutput(text);

			player.hasBall(true);
			player.setState(State::Attack);
			player.setTarget(*player.getOpponentGoalPosition());

			opponent->hasBall(false);
			opponent->setState(State::Idle);
			opponent->setTarget(Position(0, 0));
		}
		else
		{
			text = ", doch der bleibt am Ball.\n\n";
			std::cout << text;
			Match::addTextOutput(text);

			player.hasBall(false);
			player.setState(State::Idle);
			player.setTarget(Position(0, 0));

			opponent->hasBall(true);
			opponent->setState(State::Attack);
			opponent->setTarget(*opponent->getOpponentGoalPosition());
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(Match::textSpeed));
	}

	player.setState(State::Move);
	player.setTarget(*ball.getPosition());

	endTurn(player, pitch);
}