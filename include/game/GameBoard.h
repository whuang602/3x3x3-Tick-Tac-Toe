#pragma once

#include <iostream>
#include <vector>
#include "GoalPost.h"
#include <utility>
#include <functional>

#include "utility.h"

class GameBoard {
public:
    GameBoard();
    int removeBall(int x, int y);
    bool addBall(int player, int x, int y);

    Vector2D<int> getLayerX(int x) const;
    Vector2D<int> getLayerY(int y) const;
    Vector2D<int> getLayerZ(int z) const;
    Vector2D<int> getLayer(char c, int i) const;

    bool isFull() const;
    string flatten() const;

    vector<pair<int, int>> getAvailableRemoves() const;
    vector<pair<int, int>> getAvailableAdds() const;

private:
    Vector2D<int> getLayer(function<vector<int>(int itr)> func) const;
    
    Vector2D<GoalPost> board;
    int numBalls;
};
