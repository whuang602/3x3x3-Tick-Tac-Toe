#pragma once
#include "../game/Game.h"
#include "State.h"
#include <random>
#include <string>

#include <vector>
#include <utility>

class AIGame : public Game {
	public:
		AIGame(int playerId);
		bool makeMove(std::string move, int x, int y);
		void displayBoard() const;
	private:
		void AIMakeMove();
		Move getMove();
		const int PLAYER_ID;
		State state;
};
