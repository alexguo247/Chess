#include "bishop.h"
#include "board.h"

#include <cmath>
using namespace std;
Bishop::Bishop(Colour c, int row, int col, bool hasMoved) : Piece(c, Type::BISHOP, row, col, hasMoved){};

bool Bishop::checkMove(pair<int, int> n, Board *b)
{
    if (row == n.first && col == n.second)
    {
        return false;
    }
    if (n.first < 0 || n.first > 7 || n.second < 0 || n.second > 7)
    {
        return false;
    }
    if (abs((double)(n.second - col) / (n.first - row)) != 1.0)
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

    // Down right diagonal
    if (rowDiff > 0 && colDiff > 0)
    {
        for (int i = 1; i < rowDiff; i++)
        {
            if (b->getPiece(row + i, col + i) != nullptr)
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
    // Up left diagonal
    else
    {
        for (int i = 1; i < (-1 * rowDiff); i++)
        {
            if (b->getPiece(row - i, col - i) != nullptr)
            {
                return false;
            }
        }
    }

    return true;
}

vector<vector<int>> Bishop::getAttackMoves(Board &b)
{
    vector<vector<int>> attackMoves;
    int currRow = row;
    int currCol = col;
    // Down right
    while (currRow < 8 && currCol < 8 && b.getPiece(currRow, currCol) == nullptr)
    {
        attackMoves.push_back({currRow, currCol, row, col});
        currRow++;
        currCol++;
    }
    if (currRow < 8 && currCol < 8 && b.getPiece(currRow, currCol)->getColour() != colour)
    {
        attackMoves.push_back({currRow, currCol, row, col});
    }
    currRow = row;
    currCol = col;
    // Top left
    while (currRow >= 0 && currCol >= 0 && b.getPiece(currRow, currCol) == nullptr)
    {
        attackMoves.push_back({currRow, currCol, row, col});
        currRow--;
        currCol--;
    }
    if (currRow >= 0 && currCol >= 0 && b.getPiece(currRow, currCol)->getColour() != colour)
    {
        attackMoves.push_back({currRow, currCol, row, col});
    }
    currRow = row;
    currCol = col;
    // Bottom left
    while (currRow < 8 && currCol >= 0 && b.getPiece(currRow, currCol) == nullptr)
    {
        attackMoves.push_back({currRow, currCol, row, col});
        currRow++;
        currCol--;
    }
    if (currRow < 8 && currCol >= 0 && b.getPiece(currRow, currCol)->getColour() != colour)
    {
        attackMoves.push_back({currRow, currCol, row, col});
    }
    currRow = row;
    currCol = col;
    // Top right
    while (currRow >= 0 && currCol < 8 && b.getPiece(currRow, currCol) == nullptr)
    {
        attackMoves.push_back({currRow, currCol, row, col});
        currRow--;
        currCol++;
    }
    if (currRow >= 0 && currCol < 8 && b.getPiece(currRow, currCol)->getColour() != colour)
    {
        attackMoves.push_back({currRow, currCol, row, col});
    }
    return attackMoves;
}