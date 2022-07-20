#include "human.h"
#include "piece.h"
#include <iostream>

using namespace std; 

void Human::move(pair<int, int> start, pair<int, int> end) {
    Piece *p = b->getPiece(start.first, start.second);

    if (!p->checkMove(end, b)) {
        cout << "Invalid move!" << endl;
        return;
    }

    p->move(end, b);
};