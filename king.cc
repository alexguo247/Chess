#include "king.h"
#include "board.h"
#include <cmath>
#include <iostream>
using namespace std;

King::King(Colour c, int row, int col, bool hasMoved) : Piece(c, Type::KING, row, col, hasMoved){};

bool King::checkMove(pair<int, int> n, Board &b)
{
    if (row == n.first && col == n.second)
    {
        return false;
    }
    if (n.first < 0 || n.first > 7 || n.second < 0 || n.second > 7)
    {
        return false;
    }

    if (b.inDanger(colour, n.first, n.second))
    {
        return false;
    }
    // Castling
    if (row == n.first && abs(n.second - col) == 2)
    {
        // Castling check
        if (!hasMoved)
        {
            if (this->getColour() == Colour::WHITE)
            {
                if (n.second - col == 2)
                {
                    if (b.getPiece(7, 5) == nullptr && b.getPiece(7, 6) == nullptr && b.getPiece(7, 7) != nullptr && !b.getPiece(7, 7)->getHasMoved() && b.getPiece(7, 7)->getType() == Type::ROOK)
                    {
                        return true;
                    }
                }
                else
                {
                    if (b.getPiece(7, 1) == nullptr && b.getPiece(7, 2) == nullptr && b.getPiece(7, 3) == nullptr && b.getPiece(7, 0) != nullptr && !b.getPiece(7, 0)->getHasMoved() && b.getPiece(7, 7)->getType() == Type::ROOK)
                    {
                        return true;
                    }
                }
            }
            else
            {
                if (n.second - col == 2)
                {
                    if (b.getPiece(0, 5) == nullptr && b.getPiece(0, 6) == nullptr && b.getPiece(0, 7) != nullptr && !b.getPiece(0, 7)->getHasMoved() && b.getPiece(0, 7)->getType() == Type::ROOK)
                    {
                        return true;
                    }
                }
                else
                {
                    if (b.getPiece(0, 1) == nullptr && b.getPiece(0, 2) == nullptr && b.getPiece(0, 3) == nullptr && b.getPiece(0, 0) != nullptr && !b.getPiece(0, 0)->getHasMoved() && b.getPiece(0, 0)->getType() == Type::ROOK)
                    {
                        return true;
                    }
                }
            }
        }
        else
        {
            return false;
        }
        return false;
    }
    else
    {
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
            if (n.first == row + d.first && n.second == col + d.second && (b.getPiece(n.first, n.second) == nullptr || b.getPiece(n.first, n.second)->getColour() != colour))
            {
                return true;
            }
        }
        return false;
    }
}

vector<vector<int>> King::getAttackMoves(Board &b, int count)
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
        if (newRow < 0 || newCol < 0 || newRow >= 8 || newCol >= 8)
        {
            continue;
        }
        if ((b.getPiece(newRow, newCol) == nullptr || b.getPiece(newRow, newCol)->getColour() != colour) && !b.inDanger(Colour::BLACK, newRow, newCol))
        {
            attackMoves.push_back({newRow, newCol, row, col});
        }
    }
    return attackMoves;
}