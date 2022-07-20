#include <piece.h>
#include <string>

using namespace std;

Type Piece::getType() { return type; }

Colour Piece::getColour() { return colour; }

pair<int, int> Piece::getPos()
{
    return make_pair(row, col);
}

void Piece::setPos(int x, int y) {
    row = x;
    col = y;
}

void Piece::move(pair<int, int> end, Board *b) {
    b->setPiece(this, end.first, end.second);
    b->setPiece(nullptr, row, col);
    p->setPos(end.first, end.second);
}


bool Piece::isMoved()
{
    return isMoved;
}

void Piece::setMove(bool m) {}

bool Piece::isRiskyMove(int r, int c, int nr, int nc) {}

void Piece::notifyObservers() {}