#include "pawn.h"
#include <cmath>
using namespace std;

Pawn::Pawn(Colour c, int row, int col) : Piece(c, Type::PAWN, row, col){};

bool Pawn::checkMove(int r, int c, int nr, int nc, Board *b)
{
    if (r == nr && c == nc)
    {
        return false;
    }
    if (nr < 0 || nr > 7 || nc < 0 || nc > 7)
    {
        return false;
    }

    int rowDiff = nr - r;
    int colDiff = nc - c;
    if (colour == Colour::BLACK)
    {
        if ((colDiff == 1 || colDiff == -1) && rowDiff == 1)
        {
            if (b->getPiece(nr, nc)->getColour() != colour)
            {
                return true;
            }
            return false;
        }
        if (hasMoved)
        {
            if (rowDiff == 1 && b->getPiece(nr, nc) == nullptr)
            {
                return true;
            }
            return false;
        }
        else
        {
            if ((rowDiff == 1 || rowDiff == 2) && b->getPiece(nr, nc) == nullptr)
            {
                return true;
            }
            return false;
        }
    }
    else
    {
        if ((colDiff == 1 || colDiff == -1) && rowDiff == -1)
        {
            if (b->getPiece(nr, nc)->getColour() != colour)
            {
                return true;
            }
            return false;
        }
        if (hasMoved)
        {
            if (rowDiff == -1 && b->getPiece(nr, nc) == nullptr)
            {
                return true;
            }
            return false;
        }
        else
        {
            if ((rowDiff == -1 || rowDiff == -2) && b->getPiece(nr, nc) == nullptr)
            {
                return true;
            }
            return false;
        }
    }

    return false;
}