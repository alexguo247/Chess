#include "human.h"
#include "piece.h"
#include <iostream>

using namespace std; 

void Human::move(pair<int, int> start, pair<int, int> end, pair<int, int> &kingPos) {
    Piece *p = b->getPiece(start.first, start.second);

    if (!p->checkMove(end, b)) {
        cout << "Invalid move!" << endl;
    }

    p->move(end, b);
    if (p->getType() == Type::KING) {
        kingPos = end;
    }
};