#include "knight.h"
#include <cmath>
using namespace std;

Knight::Knight(Colour c) : Piece(c, Type::Knight){};

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
        if (nr == r + d.first && nc == c + d.second && b->getPiece(nr, nc).type == Type::Empty)
        {
            return true;
        }
    }

    return false;
}