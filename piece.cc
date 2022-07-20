#include <piece.h>
#include <string>

using namespace std;

Type Piece::getType() { return type; }

Colour Piece::getColour() { return colour; }

pair<int, int> Piece::getPos() { return pair<int, int>{row, col}; }

void Piece::setPos(int x, int y)
{
    row = x;
    col = y;
}

void Piece::move(int r, int c, int nr, int nc) {}

bool Piece::isMoved() {}

void Piece::setMove(bool m) {}

bool Piece::isRiskyMove(int r, int c, int nr, int nc) {}

void Piece::notifyObservers() {}