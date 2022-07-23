#include "piece.h"
#include "board.h"
#include <string>
#include <iostream>

using namespace std;

Type Piece::getType() { return type; }

Colour Piece::getColour() { return colour; }

Piece::Piece(Colour c, Type t, int row, int col, bool hasMoved) : colour{c}, type{t}, row{row}, col{col}, hasMoved{hasMoved} {};

pair<int, int> Piece::getPos() { return pair<int, int>{row, col}; }

Piece::~Piece(){};

void Piece::setPos(int x, int y)
{
    row = x;
    col = y;
}

bool Piece::getHasMoved()
{
    return hasMoved;
}