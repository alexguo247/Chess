#include "rook.h"
#include "board.h"
#include <cmath>
#include <iostream>
using namespace std;

Rook::Rook(Colour c, int row, int col, bool hasMoved) : Piece(c, Type::ROOK, row, col, hasMoved){};

bool Rook::checkMove(pair<int, int> n, Board &b)
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
    if (b.getPiece(n.first, n.second) != nullptr && b.getPiece(n.first, n.second)->getColour() == colour)
    {
        return false;
    }

    if (b.causesCheck(this, n))
    {
        return false;
    }

    // Down
    if (rowDiff > 0 && colDiff == 0)
    {
        for (int i = 1; i < rowDiff; i++)
        {
            if (b.getPiece(row + i, col) != nullptr)
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
            if (b.getPiece(row - i, col) != nullptr)
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
            if (b.getPiece(row, col - i) != nullptr)
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
            if (b.getPiece(row, col + i) != nullptr)
            {
                return false;
            }
        }
    }

    return true;
}

vector<vector<int>> Rook::getAttackMoves(Board &b)
{
    vector<vector<int>> attackMoves;

    int currRow = row + 1;
    int currCol = col;
    // Down
    while (currRow < 8 && b.getPiece(currRow, currCol) == nullptr && !b.causesCheck(this, {currRow, currCol}))
    {
        attackMoves.push_back({currRow, currCol, row, col});
        currRow++;
    }
    if (currRow < 8 && b.getPiece(currRow, currCol)->getColour() != colour && !b.causesCheck(this, {currRow, currCol}))
    {
        attackMoves.push_back({currRow, currCol, row, col});
    }
    currRow = row - 1;
    // Up
    while (currRow >= 0 && b.getPiece(currRow, currCol) == nullptr && !b.causesCheck(this, {currRow, currCol}))
    {
        attackMoves.push_back({currRow, currCol, row, col});
        currRow--;
    }
    if (currRow >= 0 && b.getPiece(currRow, currCol)->getColour() != colour && !b.causesCheck(this, {currRow, currCol}))
    {
        attackMoves.push_back({currRow, currCol, row, col});
    }

    currRow = row;
    currCol = col - 1;

    // Left
    while (currCol >= 0 && b.getPiece(currRow, currCol) == nullptr && !b.causesCheck(this, {currRow, currCol}))
    {
        attackMoves.push_back({currRow, currCol, row, col});
        currCol--;
    }
    if (currCol >= 0 && b.getPiece(currRow, currCol)->getColour() != colour && !b.causesCheck(this, {currRow, currCol}))
    {
        attackMoves.push_back({currRow, currCol, row, col});
    }
    currCol = col + 1;
    // Right
    while (currCol < 8 && b.getPiece(currRow, currCol) == nullptr && !b.causesCheck(this, {currRow, currCol}))
    {
        attackMoves.push_back({currRow, currCol, row, col});
        currCol++;
    }
    if (currCol < 8 && b.getPiece(currRow, currCol)->getColour() != colour && !b.causesCheck(this, {currRow, currCol}))
    {
        attackMoves.push_back({currRow, currCol, row, col});
    }
    return attackMoves;
}