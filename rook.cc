#include "rook.h"
#include <cmath>
using namespace std;
Rook::Rook(Colour c, int row, int col) : Piece(c, Type::ROOK, row, col){};

bool Rook::checkMove(int r, int c, int nr, int nc, Board *b)
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
            if (b->getPiece(r + i, c) != nullptr)
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
            if (b->getPiece(r - i, c) != nullptr)
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
            if (b->getPiece(r, c - i) != nullptr)
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
            if (b->getPiece(r, c + i) != nullptr)
            {
                return false;
            }
        }
    }

    return true;
}

vector<pair<int, int>> Rook::getAttackMoves(Board *b)
{
    vector<pair<int, int>> attackMoves;
    int currRow = row;
    int currCol = col;
    // Down
    while (currRow < 8 && b->getPiece(currRow, currCol) == nullptr)
    {
        attackMoves.emplace_back(make_pair(currRow, currCol));
        currRow++;
    }
    if (currRow < 8 && b->getPiece(currRow, currCol)->getColour() != colour)
    {
        attackMoves.emplace_back(make_pair(currRow, currCol));
    }
    currRow = row;
    // Up
    while (currRow >= 0 && b->getPiece(currRow, currCol) == nullptr)
    {
        attackMoves.emplace_back(make_pair(currRow, currCol));
        currRow--;
    }
    if (currRow >= 0 && b->getPiece(currRow, currCol)->getColour() != colour)
    {
        attackMoves.emplace_back(make_pair(currRow, currCol));
    }
    currRow = row;
    // Left
    while (currCol >= 0 && b->getPiece(currRow, currCol) == nullptr)
    {
        attackMoves.emplace_back(make_pair(currRow, currCol));
        currCol--;
    }
    if (currCol >= 0 && b->getPiece(currRow, currCol)->getColour() != colour)
    {
        attackMoves.emplace_back(make_pair(currRow, currCol));
    }
    currCol = col;
    // Right
    while (currCol < 8 && b->getPiece(currRow, currCol) == nullptr)
    {
        attackMoves.emplace_back(make_pair(currRow, currCol));
        currCol++;
    }
    if (currCol < 8 && b->getPiece(currRow, currCol)->getColour() != colour)
    {
        attackMoves.emplace_back(make_pair(currRow, currCol));
    }
    return attackMoves;
}