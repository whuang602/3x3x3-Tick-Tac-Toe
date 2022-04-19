#include <iostream>
#include <regex>
#include <vector>
#include <utility>
#include "../../include/ai/AIGame.h"
#include "../../include/ai/State.h"
#include "../../include/game/Game.h"
#include "../../include/game/utility.h"

AIGame::AIGame(int playerId) : PLAYER_ID(playerId) {
	if (playerId == 2) {
		makeMove("", -1, -1);
	}
	state.readPolicy();
}

bool AIGame::makeMove(std::string move, int x, int y) {
	bool playerMove = Game::makeMove(move, x, y); //it's important to specify the game here

	while (whoseTurn() != PLAYER_ID && !finished()) {
		this->AIMakeMove();    
	}
	
	return playerMove;
}

void AIGame::AIMakeMove(){
	Move m = getMove();
	Game::makeMove(m.add_rem, m.x, m.y);
}

Move AIGame::getMove(){
	// if policy is empty then do random:
	srand(time(0));

	unordered_map<string, Move> possible_moves = Game::get_possibilities();

	if(possible_moves.size() == 0){
		cerr << "no possible moves ya dingus" << endl;
		exit(1);
	}

	if(state.size() == 0 || (rand() % 100) <= 0.3 * 100){
		unordered_map<string, Move>::iterator item = possible_moves.begin();
		
		int move_index = rand() % possible_moves.size();
		advance(item, move_index);

		return item->second;
	}

	string g_key;
	bool foundValue = false;

	for(pair<string, Move> state_move : possible_moves){
		if(state.has_key(state_move.first) &&
			(!foundValue ||
			state.get(state_move.first, Game::whoseTurn()) >
			state.get(g_key, Game::whoseTurn()))) {

			g_key = state_move.first;	
			foundValue = true;
		}
	}
	return possible_moves[g_key];
}

void AIGame::displayBoard() const {
	string player1Name = PLAYER_ID == 1 ? "Player" : "Computer";
	string player2Name = PLAYER_ID == 2 ? "Player" : "Computer";

	string display = (
		"               *     *     *\n"
		"               *     *     *              Current Score\n"
		"               * --- * --- *              " + player1Name + ": O : " + to_string(getScore(1)) + "\n"  
		"           *  /  *  /  *  /               " + player2Name + ": X : " + to_string(getScore(2)) + "\n" 
		"           * /   * /   * /\n"
		"           * --- * --- *                  It is " + (whoseTurn() == 1 ? player1Name : player2Name) + "'s turn.\n" 
		"       *  /  *  /  *  /                     - " + to_string(movesRemaining()) + " moves remaining.\n"
		"       * /   * /   * /                      - " + to_string(canRemove()) + " remove remaining.\n"
		"       * --- * --- *                        - " + to_string(ballsLeft()) + " balls left.\n"
	);
	
	vector<int> ball_indices;
	for(int i = 0; i < display.size(); i++){
		if(display[i] == '*'){
			ball_indices.push_back(i);
		}
	}

	std::string balls = gameboard.flatten();

	for(int i = 0; i < 27; i++){
		display = drawBall(display, ball_indices[i], balls[i] - '0');
	}

	cout << display << endl;
}
