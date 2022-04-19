#include "../../include/game/utility.h"
#include "../../include/game/GameParams.h"
#include <functional>
#include <vector>
#include <utility>
#include <sstream>
#include <iterator>

vector<pair<int, int>> crossing(int a, int b) {
    vector<pair<int, int>> output(a * b);

    for (int i = 0; i < a; ++i) {
        for (int j = 0; j < b; ++j) {
            output[i * b + j] = pair<int, int>(i, j);
        }
    }

    return output;
}

vector<triple> crossing(int a, int b, int c) {
    vector<triple> output (a * b * c);

    for (int i = 0; i < a; ++i) {
        for (int j = 0; j < b; ++j) {
            for (int k = 0; k < c; ++k) {
                output[i * b * c + j * c + k] = {i, j, k};
            }
        }
    }

    return output;
}

bool inRange(int val, int upper, int lower) {
    return val >= lower && val < upper;
}

bool isSame(vector<int> v){
	return v[0] == v[1] && v[1] == v[2];
}

// checks if all of the columns in a 2d vector have same value and adds corresponding score
pair<int, int> countVertical(Vector2D<int> layer) {
	int x = 0, y = 0;
	// go through each columns:
	for (int i = 0; i < layer.size(); ++i) {
		// first value in column:
		int player = layer[i][0];

		// if player had ball and the column is the same, increment values
		if (player && isSame(layer[i])) {
			player == 1 ? ++x : ++y;
		}
	}

	return pair<int, int>(x, y);
}

// checks if all of the rows in a 2d vector have same value and adds corresponding score
pair<int, int> countHorizontal(Vector2D<int> layer) {
	int x = 0, y = 0;
	for (int i = 0; i < layer.size(); ++i) {
		// first value in row
		int player = layer[0][i];

		// build up row
		std::vector<int> row(layer[i].size());
		for (int j = 0; j < row.size(); ++j) {
			row[j] = layer[j][i];
		}

		// check with row
		if (player && isSame(row)) {
			player == 1 ? ++x : ++y;
		}
	}
	return pair<int, int>(x, y);
}

pair<int, int> countDiag(Vector2D<int> layer) {
	int mid = layer[1][1];
	if(mid == 0){
		return pair<int, int>(0, 0);
	}

	vector<int> diag1 = {layer[0][0], mid, layer[2][2]},
				diag2 = {layer[0][2], mid, layer[2][0]};
	int score = isSame(diag1) + isSame(diag2);

	return mid == 1 
		? pair<int, int>(score, 0) 
		: pair<int, int>(0, score);
}

pair<int, int> countDiag3D(vector<Vector2D<int> > layer) {
	int mid = layer[1][1][1];
	if(mid == 0){
		return pair<int, int>(0, 0);
	}

	vector<int> diag1 = {layer[0][0][0], mid, layer[2][2][2]},
				diag2 = {layer[0][2][2], mid, layer[2][0][0]};

	int score = isSame(diag1) + isSame(diag2);

	return mid == 1 
		? pair<int, int>(score, 0) 
		: pair<int, int>(0, score);
}

vector<pair<int, int>> getAvailable(Vector2D<int> layer, function<bool(int)> condition) {
	vector<pair<int, int>> output;

	for (pair<int, int> p : ORDERED_PAIRS) {
		if (condition(layer[p.first][p.second])) {
			output.push_back(p);
		}
	}

	return output;
}

string serialize(vector<int> input) {
    std::stringstream result;
    std::copy(input.begin(), input.end(), std::ostream_iterator<int>(result, ""));
    return result.str();
}