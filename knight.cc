#include "knight.h"
#include <cmath>
using namespace std;

Knight::Knight(Colour c, int row, int col) : Piece(c, Type::KNIGHT, row, col){};

bool Knight::checkMove(pair<int, int> n, Board *b)
{
    if (row == n.first && col == n.second)
    {
        return false;
    }
    if (n.first < 0 || n.first > 7 || n.second < 0 || n.second > 7)
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
        if (n.first == row + d.first && n.second == col + d.second && b->getPiece(n.first, n.second) == nullptr)
        {
            return true;
        }
    }

    return false;
}

vector<vector<int>> Knight::getAttackMoves(Board *b)
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
        if (b->getPiece(newRow, newCol) == nullptr || b->getPiece(newRow, newCol)->getColour() != colour)
        {
            attackMoves.emplace_back(newRow, newCol, row, col);
        }
    }
    return attackMoves;
}