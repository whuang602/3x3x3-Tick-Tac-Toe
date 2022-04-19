#include "../../include/game/GameBoard.h"
#include "../../include/game/utility.h"
#include <functional>

using namespace std;

GameBoard::GameBoard() : board(SIZE) {
	for (int i = 0; i < SIZE; ++i) {
		// set each element to a vector of size SIZE, passing in SIZE to the constructor of GoalPost
		board[i] = vector<GoalPost>(SIZE, SIZE);
	}
	numBalls = 0;
}

int GameBoard::removeBall(int x, int y) {
	if (!inRange(x, SIZE) || !inRange(y, SIZE)) {
		return false;
	}
	int result = board[x][y].pop();

	if (result) {
		--numBalls;
	}

	return result;
}

bool GameBoard::addBall(int player, int x, int y) {
	if (!inRange(x, SIZE) || !inRange(y, SIZE)) {
		return false;
	}
	bool result = board[x][y].push(player);

	if (result) {
		++numBalls;
	}

	return result;
}

Vector2D<int> GameBoard::getLayer(char c, int i) const {
	switch(c){
		case 'x':
			return getLayerX(i);
		case 'y':
			return getLayerY(i);
		case 'z':
			return getLayerZ(i);
	}
	return {{-1}};
}

Vector2D<int> GameBoard::getLayer(function<vector<int>(int itr)> col) const {
	Vector2D<int> output(SIZE);

	for (int i = 0; i < SIZE; ++i) {
		output[i] = fillVector(col(i), SIZE);
	}

	return output;
}

Vector2D<int> GameBoard::getLayerX(int x) const {
	return getLayer([this, x](int itr){
		return this->board[x][itr].getPost();
	});
}

Vector2D<int> GameBoard::getLayerY(int y) const {
	return getLayer([this, y](int itr){
		return this->board[itr][y].getPost();
	});
}

Vector2D<int> GameBoard::getLayerZ(int z) const {
	return getLayer([this, z](int itr){
		vector<int> output = vector<int>(SIZE);

		// build row
		for (int y = 0; y < SIZE; ++y) {
			vector<int> col = board[itr][y].getPost();
			output[y] = fillVector(col, SIZE)[z];
		}
		
		return output;
	});
}

bool GameBoard::isFull() const {
	//return numBalls == SIZE * SIZE * SIZE;
	return getAvailableAdds().size() == 0;
}

string GameBoard::flatten() const {
	//vector<int> balls;
	string balls = "";

	for (triple t : ORDERED_TRIPLES) {
		balls += to_string(getLayerY(t.first)[t.third][SIZE - t.second - 1]);
	}

	return balls;
}

vector<pair<int, int>> GameBoard::getAvailableRemoves() const {
	// bottom layer isn't a zero (there is a value to remove)
	return getAvailable(getLayerZ(0), [](int a){ return a != 0; });
}

vector<pair<int, int>> GameBoard::getAvailableAdds() const {
	// top layer is a zero (there is a space to add)
	return getAvailable(getLayerZ(SIZE - 1), [](int a){ return a == 0; });	
}
