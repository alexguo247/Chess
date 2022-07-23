#include "piece.h"
#include "board.h"
#include <string>
#include <iostream>

using namespace std;

Type Piece::getType() { return type; }

Colour Piece::getColour() { return colour; }

Piece::Piece(Colour c, Type t, int row, int col) : colour{c}, type{t}, row{row}, col{col} { hasMoved = false; };

pair<int, int> Piece::getPos() { return pair<int, int>{row, col}; }

Piece::~Piece(){};

void Piece::setPos(int x, int y)
{
    row = x;
    col = y;
}

void Piece::move(pair<int, int> end, Board *b)
{
    pair<int, int> old = pair<int, int>{row, col};
    b->setPiece(this, end.first, end.second);
    if (b->getPiece(end.first, end.second) == this)
    {
        cout << "EQUALS THIS" << endl;
    }
    setPos(end.first, end.second);
    b->setPiece(nullptr, old.first, old.second);
    // if (b->getPiece(end))
}

bool Piece::getHasMoved()
{
    return hasMoved;
}