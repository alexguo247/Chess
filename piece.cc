#include <piece.h>
#include <string>

using namespace std;

Type Piece::getType() { return type; }

Colour Piece::getColour() { return colour; }

pair<int, int> Piece::getPos()
{
    return make_pair(row, col);
}

void Piece::setPos(int row, int col)
{
    this->row = row;
    this->col = col;
}

void Piece::move(int r, int c, int nr, int nc) {}

bool Piece::isMoved()
{
    return isMoved;
}

void Piece::setMove(bool m) {}

bool Piece::isRiskyMove(int r, int c, int nr, int nc) {}

void Piece::notifyObservers() {}