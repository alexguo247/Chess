#include "pawn.h"
#include <cmath>
using namespace std;

Pawn::Pawn(Colour c, int row, int col) : Piece(c, Type::PAWN, row, col){};

bool Pawn::checkMove(pair<int, int> n, Board *b)
{
    if (row == n.first && col == n.second)
    {
        return false;
    }
    if (n.first < 0 || n.first > 7 || n.second < 0 || n.second > 7)
    {
        return false;
    }

    int rowDiff = n.first - row;
    int colDiff = n.second - col;
    if (colour == Colour::BLACK)
    {
        if ((colDiff == 1 || colDiff == -1) && rowDiff == 1)
        {
            if (b->getPiece(n.first, n.second)->getColour() != colour)
            {
                return true;
            }
            return false;
        }
        if (hasMoved)
        {
            if (rowDiff == 1 && b->getPiece(n.first, n.second) == nullptr)
            {
                return true;
            }
            return false;
        }
        else
        {
            if ((rowDiff == 1 || rowDiff == 2) && b->getPiece(n.first, n.second) == nullptr)
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
            if (b->getPiece(n.first, n.second)->getColour() != colour)
            {
                return true;
            }
            return false;
        }
        if (hasMoved)
        {
            if (rowDiff == -1 && b->getPiece(n.first, n.second) == nullptr)
            {
                return true;
            }
            return false;
        }
        else
        {
            if ((rowDiff == -1 || rowDiff == -2) && b->getPiece(n.first, n.second) == nullptr)
            {
                return true;
            }
            return false;
        }
    }

    return false;
}