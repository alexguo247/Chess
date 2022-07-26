#include "knight.h"
#include "board.h"
#include <cmath>
#include <iostream>
using namespace std;

Knight::Knight(Colour c, int row, int col, bool hasMoved) : Piece(c, Type::KNIGHT, row, col, hasMoved){};

bool Knight::checkMove(pair<int, int> n, Board &b)
{
    if (row == n.first && col == n.second)
    {
        return false;
    }
    if (n.first < 0 || n.first > 7 || n.second < 0 || n.second > 7)
    {
        return false;
    }
    if (b.causesCheck(this, n, 0))
    {
        return false;
    }

    vector<pair<int, int>> dirs{
        pair<int, int>{-1, -2},
        pair<int, int>{-2, -1},
        pair<int, int>{-2, 1},
        pair<int, int>{-1, 2},
        pair<int, int>{1, -2},
        pair<int, int>{2, -1},
        pair<int, int>{2, 1},
        pair<int, int>{1, 2},
    };

    for (auto &d : dirs)
    {
        if (n.first == row + d.first && n.second == col + d.second && (b.getPiece(n.first, n.second) == nullptr || (b.getPiece(n.first, n.second) != nullptr && b.getPiece(n.first, n.second)->getColour() != colour)))
        {
            return true;
        }
    }

    return false;
}

vector<vector<int>> Knight::getAttackMoves(Board &b, int count)
{
    vector<vector<int>> attackMoves;
    vector<pair<int, int>> dirs{
        pair<int, int>{-1, -2},
        pair<int, int>{-2, -1},
        pair<int, int>{-2, 1},
        pair<int, int>{-1, 2},
        pair<int, int>{1, -2},
        pair<int, int>{2, -1},
        pair<int, int>{2, 1},
        pair<int, int>{1, 2},
    };

    for (auto &d : dirs)
    {
        int newRow = row + d.first;
        int newCol = col + d.second;
        if (newRow < 0 || newCol < 0 || newRow >= 8 || newCol >= 8)
        {
            continue;
        }

        if ((b.getPiece(newRow, newCol) == nullptr || b.getPiece(newRow, newCol)->getColour() != colour) && count <= 1 && !b.causesCheck(this, {newRow, newCol}, count))
        {
            attackMoves.push_back({newRow, newCol, row, col});
        }
    }
    return attackMoves;
}
