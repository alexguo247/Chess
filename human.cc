#include "human.h"
#include "piece.h"
#include <iostream>

using namespace std; 

Human::Human(Board* board, Colour c): Player(board, c) {};

void Human::move(Board *board, pair<int, int> start, pair<int, int> end) {
    Piece *p = b->getPiece(start.first, start.second);
    if (!p->checkMove(end, b)) {
        cout << "Invalid move!" << endl;
    }

    board->setPiece(p, end.first, end.second);
    board->deletePiece(start.first, start.second);
};