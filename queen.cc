#include "queen.h"
#include <cmath>

using namespace std;

Queen::Queen(Colour c, int row, int col) : Piece(c, Type::QUEEN, row, col){};

bool Queen::checkMove(pair<int, int> n, Board *b)
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
    // Down right diagonal
    else if (rowDiff > 0 && colDiff > 0)
    {
        for (int i = 1; i < rowDiff; i++)
        {
            if (b->getPiece(row + i, col + i) != nullptr)
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
            if (b->getPiece(row + i, col - i) != nullptr)
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
    // Up right diagonal
    else if (rowDiff < 0 && colDiff > 0)
    {
        for (int i = 1; i < colDiff; i++)
        {
            if (b->getPiece(row - i, col + i) != nullptr)
            {
                return false;
            }
        }
    }
    else if (rowDiff < 0 && colDiff < 0)
    {
        for (int i = 1; i < (-1 * rowDiff); i++)
        {
            if (b->getPiece(row - i, col - i) != nullptr)
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

vector<vector<int>> Queen::getAttackMoves(Board *b)
{
    vector<vector<int>> attackMoves;
    int currRow = row;
    int currCol = col;
    // Down right
    while (currRow < 8 && currCol < 8 && b->getPiece(currRow, currCol) == nullptr)
    {
        attackMoves.emplace_back(currRow, currCol, row, col);
        currRow++;
        currCol++;
    }
    if (currRow < 8 && currCol < 8 && b->getPiece(currRow, currCol)->getColour() != colour)
    {
        attackMoves.emplace_back(currRow, currCol, row, col);
    }
    currRow = row;
    currCol = col;
    // Top left
    while (currRow >= 0 && currCol >= 0 && b->getPiece(currRow, currCol) == nullptr)
    {
        attackMoves.emplace_back(currRow, currCol, row, col);
        currRow--;
        currCol--;
    }
    if (currRow >= 0 && currCol >= 0 && b->getPiece(currRow, currCol)->getColour() != colour)
    {
        attackMoves.emplace_back(currRow, currCol, row, col);
    }
    currRow = row;
    currCol = col;
    // Bottom left
    while (currRow < 8 && currCol >= 0 && b->getPiece(currRow, currCol) == nullptr)
    {
        attackMoves.emplace_back(currRow, currCol, row, col);
        currRow++;
        currCol--;
    }
    if (currRow < 8 && currCol >= 0 && b->getPiece(currRow, currCol)->getColour() != colour)
    {
        attackMoves.emplace_back(currRow, currCol, row, col);
    }
    currRow = row;
    currCol = col;
    // Top right
    while (currRow >= 0 && currCol < 8 && b->getPiece(currRow, currCol) == nullptr)
    {
        attackMoves.emplace_back(currRow, currCol, row, col);
        currRow--;
        currCol++;
    }
    if (currRow >= 0 && currCol < 8 && b->getPiece(currRow, currCol)->getColour() != colour)
    {
        attackMoves.emplace_back(currRow, currCol, row, col);
    }
    currRow = row;
    currCol = col;
    // Down
    while (currRow < 8 && b->getPiece(currRow, currCol) == nullptr)
    {
        attackMoves.emplace_back(currRow, currCol, row, col);
        currRow++;
    }
    if (currRow < 8 && b->getPiece(currRow, currCol)->getColour() != colour)
    {
        attackMoves.emplace_back(currRow, currCol, row, col);
    }
    currRow = row;
    // Up
    while (currRow >= 0 && b->getPiece(currRow, currCol) == nullptr)
    {
        attackMoves.emplace_back(currRow, currCol, row, col);
        currRow--;
    }
    if (currRow >= 0 && b->getPiece(currRow, currCol)->getColour() != colour)
    {
        attackMoves.emplace_back(currRow, currCol, row, col);
    }
    currRow = row;
    // Left
    while (currCol >= 0 && b->getPiece(currRow, currCol) == nullptr)
    {
        attackMoves.emplace_back(currRow, currCol, row, col);
        currCol--;
    }
    if (currCol >= 0 && b->getPiece(currRow, currCol)->getColour() != colour)
    {
        attackMoves.emplace_back(currRow, currCol, row, col);
    }
    currCol = col;
    // Right
    while (currCol < 8 && b->getPiece(currRow, currCol) == nullptr)
    {
        attackMoves.emplace_back(currRow, currCol, row, col);
        currCol++;
    }
    if (currCol < 8 && b->getPiece(currRow, currCol)->getColour() != colour)
    {
        attackMoves.emplace_back(currRow, currCol, row, col);
    }
    return attackMoves;
}