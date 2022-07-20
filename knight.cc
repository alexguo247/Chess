#include "knight.h"
#include <cmath>
using namespace std;

Knight::Knight(Colour c, int row, int col) : Piece(c, Type::KNIGHT, row, col){};

bool Knight::checkMove(int r, int c, int nr, int nc, Board *b)
{
    if (r == nr && c == nc)
    {
        return false;
    }
    if (nr < 0 || nr > 7 || nc < 0 || nc > 7)
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
        if (nr == r + d.first && nc == c + d.second && (b->getPiece(nr, nc) == nullptr || b->getPiece(nr, nc)->getColour() != colour))
        {
            return true;
        }
    }

    return false;
}

vector<pair<int, int>> Knight::getAttackMoves(Board *b)
{
    vector<pair<int, int>> attackMoves;
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
            attackMoves.emplace_back(make_pair(newRow, newCol));
        }
    }
    return attackMoves;
}