#pragma once

#include "Match.h"
#include "Position.h"
#include "_functions.h"
#include "Generator.h"

int Match::textSpeed;

Match::Match()
{
	this->length = 90;
	this->minute = 1;
	this->ball = std::make_shared<Ball>();
	this->ball->setPosition(8, 5);
	this->pitch = std::make_shared<Pitch>();
}

Match::~Match()
{
}

std::shared_ptr<Ball> Match::getBall()
{
	return std::shared_ptr<Ball>(this->ball);
}

int Match::getLength() const
{
	return this->length;
}

int Match::getMinute() const
{
	return this->minute;
}

void Match::addMinute()
{
	this->minute++;
}

bool Match::hasEnded() const
{
	return this->minute > this->length;
}

void Match::addGoalTeamA()
{
	this->score.first++;
}

void Match::addGoalTeamB()
{
	this->score.second++;
}

void Match::resetScore()
{
	this->score.first = 0;
	this->score.second = 0;
}

std::list<std::string> Match::getTextOutput()
{
	return textOutput;
}

void Match::addTextOutput(std::string text)
{
	textOutput.push_back(text);
}

void Match::start()
{
	init();

	processText("SPIELSTART:\n\n");

	while (!hasEnded())
	{
		char buffer[32];
		snprintf(buffer, 32, "### Minute %02d   [%d:%d] ###\n\n", minute, score.first, score.second);
		processText(buffer);

		nextMinute();
	}

	processText("\nDas Spiel endete " + std::to_string(score.first) + ":" + std::to_string(score.second) + "\n\n");

	saveOutput();
}

void Match::init()
{
	resetScore();

	this->textSpeed = (int)TextSpeed::Instant;

	this->textOutput.clear();

	Generator generator;
	
	Position teamAGoal = Position(0, 5);
	Position teamBGoal = Position(16, 5);

	for (size_t i = 0; i < teamA.size(); i++)
	{
		teamA.at(i) = generator.getNewPlayer();
		teamA.at(i).setOpponentGoalPosition(teamBGoal);
		players.push_back(&teamA.at(i));
	}
	for (size_t i = 0; i < teamB.size(); i++)
	{
		teamB.at(i) = generator.getNewPlayer();
		teamB.at(i).setOpponentGoalPosition(teamAGoal);
		players.push_back(&teamB.at(i));
	}
}

void Match::nextMinute()
{
	std::random_shuffle(players.begin(), players.end());

	for (auto& player : players)
	{
		player->performRound(*pitch, *ball);
	}

	addMinute();

	pause(this->textSpeed);
}

void Match::saveOutput()
{
	std::cout << "Soll das Ergebnis in einer Datei gespeichert werden?\n";

	std::string input = "";

	while (input == "")
	{
		std::cout << "[J/N] ";
		std::cin >> input;

		if (input == "j" || input == "J")
		{
			writeToFile(getTextOutput());
			break;
		}
		else if(input == "n" || input == "N")
		{
			break;
		}
		else
		{
			input = "";
		}
	}
}