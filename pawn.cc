#include "pawn.h"
#include <cmath>
using namespace std;

Pawn::Pawn(Colour c) : Piece(c, Type::Pawn){};

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

vector<pair<int, int>> Pawn::getAttackMoves(Board *b)
{
    vector<pair<int, int>> attackMoves;
    if (colour == Colour::BLACK)
    {
        if (b->getPiece(row + 1, col + 1) == nullptr || b->getPiece(row + 1, col + 1)->getColour() != colour)
        {
            attackMoves.emplace_back(make_pair(row + 1, col + 1));
        }
        if (b->getPiece(row + 1, col - 1) == nullptr || b->getPiece(row + 1, col - 1)->getColour() != colour)
        {
            attackMoves.emplace_back(make_pair(row + 1, col - 1));
        }
    }
    else
    {
        if (b->getPiece(row - 1, col + 1) == nullptr || b->getPiece(row - 1, col + 1)->getColour() != colour)
        {
            attackMoves.emplace_back(make_pair(row - 1, col + 1));
        }
        if (b->getPiece(row - 1, col - 1) == nullptr || b->getPiece(row - 1, col - 1)->getColour() != colour)
        {
            attackMoves.emplace_back(make_pair(row - 1, col - 1));
        }
    }
    return attackMoves;
}
