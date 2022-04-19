#pragma once

#include <string>
#include <vector>
#include <utility>
#include <unordered_map>

#include "../ai/Dict.h"
#include "GameBoard.h"
#include "Player.h"
#include "GameParams.h"
#include <functional>

using namespace std;

const string ADD = "ADD";
const string REMOVE = "REMOVE";

class Game {
	public:
		Game();
		// Pre-Condition: Game parameters	
		//post-condition: initializes game with desired gameboard size, max number of balls per player, the winning score,
		// moves a player can make per turn, moves a player can make the first turn, max number of removes a player can make in a turn and initializes the two players and gameboard

		Game(Player p1, Player p2);

		void displayBoard() const;
		//Pre-condition: 
		//Post-condition: prints board

		bool makeMove(string move, int x, int y);
		//Pre-Condition: input for move is either ADD or REMOVE , x and y are coordinates
		//Post-Condition: returns 1 for success and 0 for failure to make move

		bool finished() const;
		//Pre-Condition: no input required
		//Post-Condition:  1 if the game is finished and 0 if it’s not

		int winner() const;

		int whoseTurn() const;
		//Pre-Condition:  no input required
		//Post-Condition:  returns the id of the player who has to make a move

		bool canRemove() const;
		//Pre-Condition:  no input required
		//Post-Condition:  returns true if the current player has a remove move available

		int movesRemaining() const;
		//Pre-Condition:  no input required
		//Post-Condition:  returns the number of moves the current player has on the turn

		int getScore(int player) const;
		//Pre-Condition: player id
		//Post-Condition:  player’s score

		int ballsLeft() const;
		//Pre-Condition: no input required
		//Post-Condition: returns the number of balls the current player has remaining
	
		//Pre-Condition: none
		//Post-Condition: returns ordered pairs of available places to add
		vector<pair<int, int>> availableAdds() const;

		//Pre-Condition: none
		//Post-Condition: returns ordered pairs of available places to remove
		vector<pair<int, int>> availableRemoves() const;
		
		//Pre-Condition: none
		//Post-Condition: returns flatten gameboard
		string flatten() const;

		string get_state_after(Move move) const;

		unordered_map<string, Move> get_possibilities() const;
		//Dict<Move, string> get_possibilities() const;

	protected:
		string drawBall(string skel, int index, int playerId) const;

        GameBoard gameboard; //gameboard structure 

	private:
		//Pre-Condition: none
		//Post-Condition: increments moves, calculates scores
		void nextMove();

		//Pre-Condition: none
		//Post-Condition: switches player and resets for next turn
		void nextTurn();
		
		std::vector<Player> player_arr;
		bool turnTracker; //true = player 1’s turn; false = player 2’s turn
		int turn;
		int moves;
		int removes;

        void set3dDiagScore();
        void set2dDiagScore();
        void setZScore();
        void setYScore();
        void setXScore();
		void setScore(std::function<pair<int, int>(int i)> func, int len);

		int maxMoves() const;
		//precondition: n/a
		//postcondition: returns the number of max moves;

		void setScores();
		//Pre-Condition:  no input required
		//Post-Condition:  calculates scores for each player

		int tryMove(std::string move, int x, int y);
		//Pre-Condition: the type of move (add/remove) and position on board
		//Post-Condition:  returns true if the move was successful  
};
