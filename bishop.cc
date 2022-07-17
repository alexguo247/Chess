#include "bishop.h"
#include <cmath>

Bishop::Bishop(Colour c) : Piece(c, Type::Bishop){};

bool Bishop::checkMove(int r, int c, int nr, int nc, Board *b)
{
    if (r == nr && c == nc)
    {
        return false;
    }
    if (nr < 0 || nr > 7 || nc < 0 || nc > 7)
    {
        return false;
    }
    if (abs((double)(nc - c) / (nr - r)) != 1.0)
    {
        return false;
    }

    int rowDiff = nr - r;
    int colDiff = nc - c;

    // If the ending spot is the same colour
    if (b->getPiece(nr, nc)->getColour() == colour)
    {
        return false;
    }

    // Down right diagonal
    if (rowDiff > 0 && colDiff > 0)
    {
        for (int i = 1; i < rowDiff; i++)
        {
            if (b->getPiece(r + i, c + i)->getType() != Type::Empty)
            {
                return false;
            }
        }
    }
    // Up right diagonal
    else if (rowDiff < 0 && colDiff > 0)
    {
        for (int i = 1; i < colDiff; i++)
        {
            if (b->getPiece(r - i, c + i)->getType() != Type::Empty)
            {
                return false;
            }
        }
    }
    // Down left diagonal
    else if (rowDiff > 0 && colDiff < 0)
    {
        for (int i = 1; i < rowDiff; i++)
        {
            if (b->getPiece(r + i, c - i)->getType() != Type::Empty)
            {
                return false;
            }
        }
    }
    // Up left diagonal
    else
    {
        for (int i = 1; i < (-1 * rowDiff); i++)
        {
            if (b->getPiece(r - i, c - i)->getType() != Type::Empty)
            {
                return false;
            }
        }
    }

    return true;
}