#pragma once
#include <vector>
#include <utility> // for pair
#include <functional>
#include "../../include/game/GameParams.h"

using namespace std;

// Typename is used to clean up code
template <class T>
using Vector2D = vector<vector<T> >;

//Pre-Condition: input: vector, end vector length, value to fill (optional)
//Post-Condition: returns a vector of the desired length
template <class T>
vector<T> fillVector(const vector<T> &input, int size, int fill = 0) {
    vector<T> output = input;
    output.resize(size, fill);
    return output;
}

//Pre-Condition: 
//Post-Condition: returns vector of all ordered pairs (0, 0) to (a-1, b-1) 
vector<pair<int, int>> crossing(int a, int b);

//Pre-Condition: 
//Post-Condition: returns vector of all ordered triples (0, 0, 0) to (a-1, b-1, c-1)
struct triple {
    int first, second, third;
};
vector<triple> crossing(int a, int b, int c);

const vector<pair<int, int>> ORDERED_PAIRS = crossing(SIZE, SIZE); // all combinations (0,0) to (2, 2)
const vector<triple> ORDERED_TRIPLES = crossing(SIZE, SIZE, SIZE); // all combinations (0, 0, 0) to (2, 2, 2)

//Pre-Condition: input: value, upper limit, lower limit
//Post-Condition: true if lower<=val<upper, false otherwise
bool inRange(int val, int upper, int lower = 0);

//Pre-Condition: vector of length 3
//Post-Condition: true if all elements in vector have same value
bool isSame(vector<int> v);

//Pre-Condition: 2D vector of ints
//Post-Condition: pair of player1, player2 score, where the score is the number of 3 in a rows along columns
pair<int, int> countVertical(Vector2D<int> layer);

//Pre-Condition: 2D vector of ints
//Post-Condition: pair of player1, player2 score, where the score is the number of 3 in a rows along rows
pair<int, int> countHorizontal(Vector2D<int> layer);

//Pre-Condition: 2D vector of ints
//Post-Condition: pair of player1, player2 score, where the scores is the number of 3 in a rows along the diagonals
pair<int, int> countDiag(Vector2D<int> layer);

//Pre-Condition: 3D vector of ints
//Post-Condition: pair of player1, player2 score, where the score is the number of 3 in arows along the largest diagonal
pair<int, int> countDiag3D(vector<Vector2D<int> > layer);

//Pre-Condition: 2D vector of ints, 
//Post-Condition: returns coordinates of layers where the condition is met by iterating over one value
vector<pair<int, int>> getAvailable(Vector2D<int> layer, function<bool(int)> condition);

string serialize(vector<int>);