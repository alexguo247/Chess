#include "human.h"
#include "piece.h"
#include <iostream>

using namespace std;

Human::Human(Board *board, Colour c) : Player(board, c){};

void Human::move(Board *board, pair<int, int> start, pair<int, int> end, char promotion)
{
    board->move(start, end, promotion);
};