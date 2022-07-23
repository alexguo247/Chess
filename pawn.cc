#include "pawn.h"
#include "board.h"
#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

Pawn::Pawn(Colour c, int row, int col, bool hasMoved) : Piece(c, Type::PAWN, row, col, hasMoved){};

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

vector<vector<int>> Pawn::getAttackMoves(Board &b)
{
    vector<vector<int>> attackMoves = {};
    if (colour == Colour::BLACK)
    {
        if ((row + 1 < 8 && col + 1 < 8) && (b.getPiece(row + 1, col + 1) == nullptr || b.getPiece(row + 1, col + 1)->getColour() != colour))
        {
            attackMoves.push_back({row + 1, col + 1, row, col});
        }
        if ((row + 1 < 8 && col - 1 >= 0) && (b.getPiece(row + 1, col - 1) == nullptr || b.getPiece(row + 1, col - 1)->getColour() != colour))
        {
            attackMoves.push_back({row + 1, col - 1, row, col});
        }
    }
    else
    {
        if ((row - 1 >= 0 && col + 1 < 8) && (b.getPiece(row - 1, col + 1) == nullptr || b.getPiece(row - 1, col + 1)->getColour() != colour))
        {
            attackMoves.push_back(vector<int>{row - 1, col + 1, row, col});
        }
        if ((row - 1 >= 0 && col - 1 >= 0) && (b.getPiece(row - 1, col - 1) == nullptr || b.getPiece(row - 1, col - 1)->getColour() != colour))
        {
            attackMoves.push_back(vector<int>{row - 1, col - 1, row, col});
        }
    }
    return attackMoves;
}
