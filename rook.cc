#include "rook.h"
#include <cmath>
using namespace std;
Rook::Rook(Colour c, int row, int col) : Piece(c, Type::ROOK, row, col){};

bool Rook::checkMove(pair<int, int> n, Board *b)
{
    if (row == n.first && col == n.second)
    {
        return false;
    }
    if (n.first < 0 || n.first > 7 || n.second < 0 || n.second > 7)
    {
        return false;
    }
    if (row != n.first && col != n.second)
    {
        return false;
    }

    int rowDiff = n.first - row;
    int colDiff = n.second - col;

    // If the ending spot is the same colour
    if (b->getPiece(n.first, n.second)->getColour() == colour)
    {
        return false;
    }

    // Down
    if (rowDiff > 0 && colDiff == 0)
    {
        for (int i = 1; i < rowDiff; i++)
        {
            if (b->getPiece(row + i, col) != nullptr)
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
            if (b->getPiece(row - i, col) != nullptr)
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
            if (b->getPiece(row, col - i) != nullptr)
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
            if (b->getPiece(row, col + i) != nullptr)
            {
                return false;
            }
        }
    }

    return true;
}

vector<vector<int>> Rook::getAttackMoves(Board *b)
{
    vector<vector<int>> attackMoves;
    int currRow = row;
    int currCol = col;
    // Down
    while (currRow < 8 && b->getPiece(currRow, currCol) == nullptr)
    {
        attackMoves.push_back({currRow, currCol, row, col});
        currRow++;
    }
    if (currRow < 8 && b->getPiece(currRow, currCol)->getColour() != colour)
    {
        attackMoves.push_back({currRow, currCol, row, col});
    }
    currRow = row;
    // Up
    while (currRow >= 0 && b->getPiece(currRow, currCol) == nullptr)
    {
        attackMoves.push_back({currRow, currCol, row, col});
        currRow--;
    }
    if (currRow >= 0 && b->getPiece(currRow, currCol)->getColour() != colour)
    {
        attackMoves.push_back({currRow, currCol, row, col});
    }
    currRow = row;
    // Left
    while (currCol >= 0 && b->getPiece(currRow, currCol) == nullptr)
    {
        attackMoves.push_back({currRow, currCol, row, col});
        currCol--;
    }
    if (currCol >= 0 && b->getPiece(currRow, currCol)->getColour() != colour)
    {
        attackMoves.push_back({currRow, currCol, row, col});
    }
    currCol = col;
    // Right
    while (currCol < 8 && b->getPiece(currRow, currCol) == nullptr)
    {
        attackMoves.push_back({currRow, currCol, row, col});
        currCol++;
    }
    if (currCol < 8 && b->getPiece(currRow, currCol)->getColour() != colour)
    {
        attackMoves.push_back({currRow, currCol, row, col});
    }
    return attackMoves;
}