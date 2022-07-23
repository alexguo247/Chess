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

bool Piece::causesCheck(Board &b, pair<int, int> n)
{
    pair<int, int> kingPos = b.findKing(colour);
    if (b.inDanger(colour, kingPos.first, kingPos.second))
    {
        return true;
    }

    int currRow = row;
    int currCol = col;
    if (b.getPiece(n.first, n.second) != nullptr)
    {
        Type t = b.getPiece(n.first, n.second)->getType();
        Colour c = b.getPiece(n.first, n.second)->getColour();
        if (c == colour)
        {
            return true;
        }
        b.setOrCreatePiece(this, n.first, n.second, false, type, colour);
        if (b.inDanger(colour, kingPos.first, kingPos.second))
        {
            b.setOrCreatePiece(this, currRow, currCol, false, type, colour);
            b.setOrCreatePiece(nullptr, n.first, n.second, true, t, c);
            return true;
        }
        else
        {
            b.setOrCreatePiece(this, currRow, currCol, false, type, colour);
            b.setOrCreatePiece(nullptr, n.first, n.second, true, t, c);
        }
    }
    else
    {
        b.setOrCreatePiece(this, n.first, n.second, false, type, colour);
        if (b.inDanger(colour, kingPos.first, kingPos.second))
        {
            b.setOrCreatePiece(this, currRow, currCol, false, type, colour);
            return true;
        }
        else
        {
            b.setOrCreatePiece(this, currRow, currCol, false, type, colour);
        }
    }
    return false;
}