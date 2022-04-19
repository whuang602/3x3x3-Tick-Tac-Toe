#include "../../include/game/Game.h"
#include "../../include/game/utility.h"
#include <functional>
#include <string>
#include <vector>
#include <utility>

using namespace std;

Game::Game() : gameboard() {
	turnTracker = false;
	turn = 0;
	nextTurn();

	Player p1(1);
	Player p2(2);
	player_arr = {p1, p2};
}

Game::Game(Player p1, Player p2) : Game() {
	player_arr = {p1, p2};
}

int Game::whoseTurn() const {
	return turnTracker ? 1 : 2;
}

bool Game::canRemove() const {
	return removes < REMOVES_PER_TURN;
}

bool Game::finished() const {
	return (
		get_possibilities().size() == 0 ||
		getScore(1) >= WINNING_SCORE ||
		getScore(2) >= WINNING_SCORE
	);
}

int Game::winner() const {
	if (!finished()) {
		return -1;
	}
	if (getScore(1) == getScore(2)) {
		return 0;
	}
	return getScore(1) > getScore(2) ? 1 : 2;
}

bool Game::makeMove(std::string move, int x, int y) {
	// try to make the move:
	int result = this->tryMove(move, x, y);

	// move was unsuccessful
	if (!result) {
		return false;
	}

	if (move == REMOVE) {
		++removes;
		player_arr[result - 1].playerRemoveBall();
	}
	else if (move == ADD) {
		player_arr[whoseTurn() - 1].playerAddBall();
	}

	nextMove();

	return true;
}

void Game::nextMove() {
	++moves;
	if (moves == maxMoves()) {
		nextTurn();
	}
	setScores();
}

void Game::nextTurn() {
	moves = 0;
	removes = 0;
	turnTracker = !turnTracker;
	++turn;
}

int Game::maxMoves() const {
	return turn == 1 
		? MOVES_FIRST_TURN 
		: MOVES_PER_TURN;
}

int Game::tryMove(std::string move, int x, int y) {
	if (move == ADD && ballsLeft()) {
		return gameboard.addBall(whoseTurn(), x, y);
	}
	if (move == REMOVE && canRemove()) {
		return gameboard.removeBall(x, y);
	}

	return false;
}

int Game::movesRemaining() const {
	return maxMoves() - moves;
}

int Game::getScore(int player) const {
	return (player > 0 && player <= NUM_PLAYERS) 
		? player_arr[player - 1].getScore()
		: -1;
}

void Game::setScores() {
	player_arr[0].setScore(0);
	player_arr[1].setScore(0);

	set3dDiagScore();
	set2dDiagScore();
	setZScore();
	setXScore();
	setYScore();
}

void Game::set3dDiagScore() {
	setScore([this](int _){
		vector<Vector2D<int> > board;
		for(int i = 0; i < 3; i++){	
			board.push_back(gameboard.getLayerZ(i));
		}
		return countDiag3D(board);
	}, 1);
}

void Game::set2dDiagScore() {
	setScore([this](int i){
		pair<int, int> p = ORDERED_PAIRS[i];
		string xyz = "xyz";

		return countDiag(gameboard.getLayer(xyz[p.first], p.second));
	}, ORDERED_PAIRS.size());
}

void Game::setScore(std::function<pair<int, int>(int i)> func, int len) {
    for (int i = 0; i < len; ++i) {
		pair<int, int> p = func(i);

		player_arr[0].addScore(p.first);
		player_arr[1].addScore(p.second);
	}
}

void Game::setZScore() {
	setScore([this](int i){
		return countVertical(gameboard.getLayerX(i));
	}, SIZE);
}

void Game::setXScore() {
	setScore([this](int i){
		return countVertical(gameboard.getLayerZ(i));
	}, SIZE);
}

void Game::setYScore() {
	setScore([this](int i){
		return countHorizontal(gameboard.getLayerZ(i));
	}, SIZE);
}

int Game::ballsLeft() const {
	return player_arr[whoseTurn() - 1].ballsLeft();
}

string Game::drawBall(string skel, int index, int playerId) const{
	string symbols = "OX";
	string replacement {playerId ? symbols[playerId - 1] : ' '};

	return skel.replace(index, 1, replacement);
}

void Game::displayBoard() const {

	string display = (
		"               *     *     *\n"
		"               *     *     *              Current Score\n"
		"               * --- * --- *              Player 1: O : " + to_string(getScore(1)) + "\n"  
		"           *  /  *  /  *  /               Player 2: X : " + to_string(getScore(2)) + "\n" 
		"           * /   * /   * /\n"
		"           * --- * --- *                  It is player " + to_string(whoseTurn()) + "'s turn.\n" 
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
	string balls = gameboard.flatten();

	for(int i = 0; i < 27; i++){
		display = drawBall(display, ball_indices[i], balls[i] - '0');
	}

	cout << display << endl;
}

vector<pair<int, int> > Game::availableAdds() const {
	return ballsLeft() 
		? gameboard.getAvailableAdds() 
		: vector<pair<int, int> >();
}

vector<pair<int, int> > Game::availableRemoves() const {
	return canRemove() 
		? gameboard.getAvailableRemoves() 
		: vector<pair<int, int> >();
}

string Game::flatten() const {
	return gameboard.flatten();
}

string Game::get_state_after(Move move) const {
	Game dummy_game = *this;
	dummy_game.makeMove(move.add_rem, move.x, move.y);
	return dummy_game.flatten();
}

unordered_map<string, Move> Game::get_possibilities() const {
	unordered_map<string, Move> possibilities;
	//Dict<Move, vector<int> > possibilities;
	vector<pair<int, int> > adds = availableAdds();
	vector<pair<int, int> > removes = availableRemoves();

	for(int i = 0; i < this->availableAdds().size(); i++){
		Move temp = {ADD, adds[i].first, adds[i].second};
		//possibilities.add(temp, get_state_after(temp));
		possibilities[get_state_after(temp)] = temp;
	}

	for(int i = 0; i < this->availableRemoves().size(); i++){
		Move temp = {REMOVE, removes[i].first, removes[i].second};
		//possibilities.add(temp, get_state_after(temp));
		possibilities[get_state_after(temp)] = temp;
	}

	return possibilities;
}

