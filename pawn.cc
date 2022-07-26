#include "pawn.h"
#include "board.h"
#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

Pawn::Pawn(Colour c, int row, int col, bool hasMoved, int doubleMove) : Piece(c, Type::PAWN, row, col, hasMoved), doubleMove{doubleMove} {};

void Pawn::setDoubleMove(int turn)
{
    doubleMove = turn;
}

bool Pawn::hasDoubleMoved()
{
    return doubleMove != -1;
}

bool Pawn::checkMove(pair<int, int> n, Board &b)
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

    int rowDiff = n.first - row;
    int colDiff = n.second - col;
    if (colour == Colour::BLACK)
    {
        // Pawn takes
        if ((colDiff == 1 || colDiff == -1) && rowDiff == 1)
        {

            Piece *p = b.getPiece(row, n.second);
            // en passant
            if (row == 4 && b.getPiece(n.first, n.second) == nullptr && p != nullptr && p->getColour() != colour && p->getType() == Type::PAWN && static_cast<Pawn *>(p)->hasDoubleMoved() && static_cast<Pawn *>(p)->doubleMove + 1 == b.turn)
            {
                p = nullptr;
                return true;
            }
            if (b.getPiece(n.first, n.second) != nullptr && b.getPiece(n.first, n.second)->getColour() != colour)
            {
                p = nullptr;
                return true;
            }
            p = nullptr;
            return false;
        }
        // Pawn normal move
        else
        {
            if (hasMoved)
            {
                if (rowDiff == 1 && b.getPiece(n.first, n.second) == nullptr)
                {
                    return true;
                }
                return false;
            }
            else
            {
                if ((rowDiff == 1 || rowDiff == 2) && b.getPiece(n.first, n.second) == nullptr)
                {
                    return true;
                }
                return false;
            }
        }
    }
    else
    {
        if ((colDiff == 1 || colDiff == -1) && rowDiff == -1)
        {
            Piece *p = b.getPiece(row, n.second); // get piece beside you
            // En passant
            if (row == 3 && b.getPiece(n.first, n.second) == nullptr && p != nullptr && p->getColour() != colour && p->getType() == Type::PAWN && static_cast<Pawn *>(p)->hasDoubleMoved() && static_cast<Pawn *>(p)->doubleMove + 1 == b.turn)
            {
                p = nullptr;
                return true;
            }
            // normal capture
            if (b.getPiece(n.first, n.second) != nullptr && b.getPiece(n.first, n.second)->getColour() != colour)
            {
                p = nullptr;
                return true;
            }
            p = nullptr;
            return false;
        }

        if (hasMoved)
        {
            if (rowDiff == -1 && b.getPiece(n.first, n.second) == nullptr)
            {
                return true;
            }
            return false;
        }
        else
        {
            if ((rowDiff == -1 || rowDiff == -2) && b.getPiece(n.first, n.second) == nullptr)
            {
                return true;
            }
            return false;
        }
    }

    return false;
}

vector<vector<int>> Pawn::getActualMoves(Board &b, int count)
{
    vector<vector<int>> attackMoves = {};
    if (colour == Colour::BLACK)
    {
        // Actual moves
        if (row + 1 < 8 && col + 1 < 8 && b.getPiece(row + 1, col + 1) != nullptr && b.getPiece(row + 1, col + 1)->getColour() != colour && count <= 1 && !b.causesCheck(this, {row + 1, col + 1}, count))
        {
            attackMoves.push_back({row + 1, col + 1, row, col});
        }
        if (row + 1 < 8 && col - 1 >= 0 && b.getPiece(row + 1, col - 1) != nullptr && b.getPiece(row + 1, col - 1)->getColour() != colour && count <= 1 && !b.causesCheck(this, {row + 1, col - 1}, count))
        {
            attackMoves.push_back({row + 1, col - 1, row, col});
        }
        if (row + 1 < 8 && b.getPiece(row + 1, col) == nullptr && count <= 1 && !b.causesCheck(this, {row + 1, col}, count))
        {
            attackMoves.push_back({row + 1, col, row, col});
        }
        if (row + 2 < 8 && b.getPiece(row + 1, col) == nullptr && b.getPiece(row + 2, col) == nullptr && !hasMoved && count <= 1 && !b.causesCheck(this, {row + 2, col}, count) && !b.causesCheck(this, {row + 1, col}, count))
        {
            attackMoves.push_back({row + 2, col, row, col});
        }
    }
    else
    {
        // Actual moves
        if (row - 1 >= 0 && col + 1 < 8 && b.getPiece(row - 1, col + 1) != nullptr && b.getPiece(row - 1, col + 1)->getColour() != colour && count <= 1 && !b.causesCheck(this, {row - 1, col + 1}, count))
        {
            attackMoves.push_back({row - 1, col + 1, row, col});
        }
        if (row - 1 >= 0 && col - 1 >= 0 && b.getPiece(row - 1, col - 1) != nullptr && b.getPiece(row - 1, col - 1)->getColour() != colour && count <= 1 && !b.causesCheck(this, {row - 1, col - 1}, count))
        {
            attackMoves.push_back({row - 1, col - 1, row, col});
        }
        if (row - 1 >= 0 && b.getPiece(row - 1, col) == nullptr && count <= 1 && !b.causesCheck(this, {row - 1, col}, count))
        {
            attackMoves.push_back({row - 1, col, row, col});
        }
        if (row - 2 >= 0 && b.getPiece(row - 1, col) == nullptr && b.getPiece(row - 2, col) == nullptr && !hasMoved && count <= 1 && !b.causesCheck(this, {row - 2, col}, count) && !b.causesCheck(this, {row - 1, col}, count))
            attackMoves.push_back({row - 2, col, row, col});
    }
    return attackMoves;
}

vector<vector<int>> Pawn::getAttackMoves(Board &b, int count)
{
    vector<vector<int>> attackMoves = {};
    if (colour == Colour::BLACK)
    {
        // Attack moves
        if (row + 1 < 8 && col + 1 < 8 && count <= 1 && !b.causesCheck(this, {row + 1, col + 1}, count))
        {
            attackMoves.push_back({row + 1, col + 1, row, col});
        }
        if (row + 1 < 8 && col - 1 >= 0 && count <= 1 && !b.causesCheck(this, {row + 1, col - 1}, count))
        {
            attackMoves.push_back({row + 1, col - 1, row, col});
        }
    }
    else
    {
        // Attack moves
        if (row - 1 >= 0 && col + 1 < 8 && count <= 1 && !b.causesCheck(this, {row - 1, col + 1}, count))
        {
            attackMoves.push_back({row - 1, col + 1, row, col});
        }
        if (row - 1 >= 0 && col - 1 >= 0 && count <= 1 && !b.causesCheck(this, {row - 1, col - 1}, count))
        {
            attackMoves.push_back({row - 1, col - 1, row, col});
        }
    }
    return attackMoves;
}
