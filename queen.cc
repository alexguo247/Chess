#include "queen.h"
#include <cmath>

Queen::Queen(Colour c) : Piece(c, Type::Queen){};

bool Queen::checkMove(int r, int c, int nr, int nc, Board *b)
{
    if (r == nr && c == nc)
    {
        return false;
    }
    if (nr < 0 || nr > 7 || nc < 0 || nc > 7)
    {
        return false;
    }
    if (r != nr && c != nc)
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

    // Down
    if (rowDiff > 0 && colDiff == 0)
    {
        for (int i = 1; i < rowDiff; i++)
        {
            if (b->getPiece(r + i, c)->getType() != Type::Empty)
            {
                return false;
            }
        }
    }
    // Down right diagonal
    else if (rowDiff > 0 && colDiff > 0)
    {
        for (int i = 1; i < rowDiff; i++)
        {
            if (b->getPiece(r + i, c + i)->getType() != Type::Empty)
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
    // Up
    else if (rowDiff < 0 && colDiff == 0)
    {
        for (int i = 1; i < (-1 * rowDiff); i++)
        {
            if (b->getPiece(r - i, c)->getType() != Type::Empty)
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
    else if (rowDiff < 0 && colDiff < 0)
    {
        for (int i = 1; i < (-1 * rowDiff); i++)
        {
            if (b->getPiece(r - i, c - i)->getType() != Type::Empty)
            {
                return false;
            }
        }
    }
    // Left
    else if (rowDiff == 0 && colDiff < 0)
    {
        for (int i = 1; i < (-1 * colDiff); i++)
        {
            if (b->getPiece(r, c - i)->getType() != Type::Empty)
            {
                return false;
            }
        }
    }
    // Right
    else
    {
        for (int i = 1; i < colDiff; i++)
        {
            if (b->getPiece(r, c + i)->getType() != Type::Empty)
            {
                return false;
            }
        }
    }

    return true;
}