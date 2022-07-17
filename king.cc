#include "king.h"
#include <cmath>
using namespace std;

King::King(Colour c) : Piece(c, Type::King){};

bool King::checkMove(int r, int c, int nr, int nc, Board *b)
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
        if (nr == r + d.first && nc == c + d.second && b->getPiece(nr, nc)->getType() == Type::Empty)
        {
            return true;
        }
    }

    return false;
}