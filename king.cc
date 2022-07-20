#include "king.h"
#include <cmath>
using namespace std;

King::King(Colour c, int row, int col) : Piece(c, Type::KING, row, col){};

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
        if (nr == r + d.first && nc == c + d.second && b->getPiece(nr, nc) == nullptr)
        {
            return true;
        }
    }

    // TODO: check if castling
    // TODO: check if going into danger spot

    return false;
}