#include <piece.h>
#include <string>

using namespace std;

Type Piece::getType() { return type; }

Colour Piece::getColour() { return colour; }

int Piece::getPos() {}

void Piece::setPos(int x, int y) {
    row = x;
    col = y;
}

void Piece::move(pair<int, int> end, Board *b) {
    b->setPiece(this, end.first, end.second);
    b->setPiece(nullptr, row, col);
    p->setPos(end.first, end.second);
}


bool Piece::isMoved() {}

void Piece::setMove(bool m) {}

bool Piece::isRiskyMove(int r, int c, int nr, int nc) {}

void Piece::notifyObservers() {}