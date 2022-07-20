#include "human.h"
#include "piece.h"
#include <iostream>

using namespace std; 

int Human::move(pair<int, int> start, pair<int, int> end) {
    Piece *p = b->getPiece(start.first, start.second);

    if (!p->checkMove(end, b)) {
        cout << "Invalid move!" << endl;
        return 0;
    }

    p->move(end, b);
    return 1;
};