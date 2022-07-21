#include "king.h"
#include "board.h"
#include <cmath>
using namespace std;

King::King(Colour c, int row, int col) : Piece(c, Type::KING, row, col){};

bool King::checkMove(pair<int, int> n, Board *b)
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
        pair<int, int>{-1, -1},
        pair<int, int>{-1, 0},
        pair<int, int>{-1, 1},
        pair<int, int>{0, -1},
        pair<int, int>{0, 1},
        pair<int, int>{1, -1},
        pair<int, int>{1, 0},
        pair<int, int>{1, 1},
    };

    for (auto &d : dirs)
    {
        if (n.first == row + d.first && n.second == col + d.second && (b->getPiece(n.first, n.second) == nullptr || b->getPiece(n.first, n.second)->getColour() != colour))
        {
            return true;
        }
    }

    // TODO: check if castling

    return false;
}

vector<vector<int>> King::getAttackMoves(Board *b)
{
    vector<vector<int>> attackMoves;
    vector<pair<int, int>> dirs{
        pair<int, int>{-1, -1},
        pair<int, int>{-1, 0},
        pair<int, int>{-1, 1},
        pair<int, int>{0, -1},
        pair<int, int>{0, 1},
        pair<int, int>{1, -1},
        pair<int, int>{1, 0},
        pair<int, int>{1, 1},
    };

    for (auto &d : dirs)
    {
        int newRow = row + d.first;
        int newCol = col + d.second;
        if (newRow < 0 || newCol < 0 || newRow >= 8 || newCol >= 8) {
            continue;
        }
        if (b->getPiece(newRow, newCol) == nullptr || b->getPiece(newRow, newCol)->getColour() != colour)
        {
            attackMoves.push_back({newRow, newCol, row, col});
        }
    }
    return attackMoves;
}