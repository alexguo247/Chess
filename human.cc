#include "human.h"
#include "piece.h"
#include <iostream>

using namespace std; 

Human::Human(Board* board, Colour c): Player(board, c) {};

void Human::move(pair<int, int> start, pair<int, int> end) {

    cout << "SOMEONE MOVING" << endl;
    Piece *p = b->getPiece(start.first, start.second);
    if (!p->checkMove(end, b)) {
        cout << "Invalid move!" << endl;
    }

    p->move(end, b);
};