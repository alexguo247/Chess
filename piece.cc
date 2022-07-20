#include <piece.h>
#include <string>

using namespace std;

Type Piece::getType() { return type; }

Colour Piece::getColour() { return colour; }

pair<int, int> Piece::getPos() { return pair<int, int>{row, col}; }

void Piece::setPos(int x, int y) {
    row = x;
    col = y;
}

void Piece::move(pair<int, int> end, Board *b) {
    pair<int, int> old = pair<int, int> {row, col};
    b->setPiece(this, end.first, end.second);
    b->setPiece(nullptr, row, col);
    setPos(end.first, end.second);
    notifyObservers(this, old);
}

bool Piece::isRiskyMove(int r, int c, int nr, int nc) {}