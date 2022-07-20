#include "chessgame.h"
#include "colour.h"
#include <iostream>
#include <cmath>

using namespace std;

pair<int, int> convertCoord(string coord)
{
    pair<int, int> convertedCoordinate;
    int row = coord[1] - '0';
    switch (coord[0])
    {
    case 'a':
        convertedCoordinate = make_pair(8 - row, 0);
        break;
    case 'b':
        convertedCoordinate = make_pair(8 - row, 1);
        break;
    case 'c':
        convertedCoordinate = make_pair(8 - row, 2);
        break;
    case 'd':
        convertedCoordinate = make_pair(8 - row, 3);
        break;
    case 'e':
        convertedCoordinate = make_pair(8 - row, 4);
        break;
    case 'f':
        convertedCoordinate = make_pair(8 - row, 5);
        break;
    case 'g':
        convertedCoordinate = make_pair(8 - row, 6);
        break;
    case 'h':
        convertedCoordinate = make_pair(8 - row, 7);
        break;
    default:
        break;
    }
    return convertedCoordinate;
}

Chessgame::Chessgame() : p1{nullptr}, p2{nullptr}, turn{Colour::WHITE}
{
    sb = new Scoreboard();
};

void Chessgame::game(string player1, string player2)
{
    p1 = player1 == "human" ? new Human(&board, Colour::WHITE) : new Computer(&board, Colour::WHITE);
    p2 = player2 == "human" ? new Human(&board, Colour::BLACK) : new Computer(&board, Colour::BLACK);
    board.setup(blackAttackingMoves, whiteAttackingMoves, blackKing, whiteKing);
}

void Chessgame::resign()
{
    if (turn == Colour::WHITE)
    {
        cout << "Black wins!" << endl;
        sb->incrementScore(Colour::BLACK);
    }
    else
    {
        cout << "White wins!" << endl;
        sb->incrementScore(Colour::WHITE);
    }
}

void Chessgame::updateAttackingMoves(Colour c)
{
    if (c == Colour::WHITE)
    {
        whiteAttackingMoves.clear();
    }
    else
    {
        blackAttackingMoves.clear();
    }

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (board.getPiece(i, j)->getColour() == c)
            {
                for (auto a : board.getPiece(i, j)->getAttackMoves(&board))
                {
                    if (c == Colour::WHITE)
                    {
                        whiteAttackingMoves.emplace_back(a);
                    }
                    else
                    {
                        blackAttackingMoves.emplace_back(a);
                    }
                }
            }
        }
    }
}

bool Chessgame::inCheck()
{
    Colour attacked = (turn == Colour::WHITE) ? Colour::BLACK : Colour::WHITE;
    int kingRow = (attacked == Colour::WHITE) ? whiteKing.first : blackKing.first;
    int kingCol = (attacked == Colour::WHITE) ? whiteKing.second : blackKing.second;
    if (inDanger(attacked, kingRow, kingCol) && !inCheckmate())
    {
        return true;
    }
    return false;
}

vector<vector<int>> Chessgame::getAttackers(Colour c)
{
    vector<vector<int>> attackers;
    if (c == Colour::BLACK)
    {
        for (auto move : whiteAttackingMoves)
        {
            if (move[0] == blackKing.first && move[1] == blackKing.second)
            {
                attackers.push_back(move);
            }
        }
    }
    else
    {
        for (auto move : blackAttackingMoves)
        {
            if (move[0] == whiteKing.first && move[1] == whiteKing.second)
            {
                attackers.push_back(move);
            }
        }
    }
    return attackers;
}

bool Chessgame::inDanger(Colour c, int row, int col)
{
    if (c == Colour::BLACK)
    {
        for (auto move : whiteAttackingMoves)
        {
            if (move[0] == row && move[1] == col)
            {
                return true;
            }
        }
    }
    else
    {
        for (auto move : blackAttackingMoves)
        {
            if (move[0] == row && move[1] == col)
            {
                return true;
            }
        }
    }
    return false;
}

bool Chessgame::canBlock(Colour c, int row, int col)
{
    if (c == Colour::BLACK)
    {
        for (auto move : blackAttackingMoves)
        {
            if (move[0] == row && move[1] == col)
            {
                return true;
            }
        }
    }
    else
    {
        for (auto move : whiteAttackingMoves)
        {
            if (move[0] == row && move[1] == col)
            {
                return true;
            }
        }
    }
    return false;
}

bool Chessgame::inCheckmate()
{
    Colour attacked = (turn == Colour::WHITE) ? Colour::BLACK : Colour::WHITE;
    vector<vector<int>> attackers = getAttackers(attacked);
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
    int kingRow = (attacked == Colour::WHITE) ? whiteKing.first : blackKing.first;
    int kingCol = (attacked == Colour::WHITE) ? whiteKing.second : blackKing.second;
    Piece *currKing = board.getPiece(kingRow, kingCol);
    // No attackers
    if (attackers.size() == 0)
    {
        return false;
    }
    // 1 attacker
    else if (attackers.size() == 1)
    {
        int attackerRow = attackers[0][2];
        int attackerCol = attackers[0][3];
        int rowDiff = attackerRow - kingRow;
        int colDiff = attackerCol - kingCol;

        // Same row (rook / queen)
        if (rowDiff == 0)
        {
            // Escape by moving away
            for (auto &d : dirs)
            {
                int nr = kingRow + d.first;
                int nc = kingRow + d.second;
                if (currKing->checkMove({nr, nc}, &board) && !inDanger(attacked, kingRow + d.first, kingCol + d.second))
                {
                    return false;
                }
            }
            // Escape by blocking
            if (colDiff > 0)
            {
                for (int i = attackerCol; i > kingCol; i--)
                {
                    if (canBlock(attacked, attackerRow, i))
                    {
                        return false;
                    }
                }
            }
            else
            {
                for (int i = attackerCol; i < kingCol; i++)
                {
                    if (canBlock(attacked, attackerRow, i))
                    {
                        return false;
                    }
                }
            }
        }
        // Same column (rook / queen)
        else if (colDiff == 0)
        {
            // Escape by moving away
            for (auto &d : dirs)
            {
                int nr = kingRow + d.first;
                int nc = kingRow + d.second;
                if (currKing->checkMove({nr, nc}, &board) && !inDanger(attacked, kingRow + d.first, kingCol + d.second))
                {
                    return false;
                }
            }
            // Escape by blocking
            if (rowDiff > 0)
            {
                for (int i = attackerRow; i > kingRow; i--)
                {
                    if (canBlock(attacked, i, attackerCol))
                    {
                        return false;
                    }
                }
            }
            else
            {
                for (int i = attackerRow; i < kingRow; i++)
                {
                    if (canBlock(attacked, i, attackerCol))
                    {
                        return false;
                    }
                }
            }
        }
        // Same diagonal (bishop / queen / pawn)
        else if (abs((double)(colDiff) / (rowDiff)) == 1.0)
        {
            double slope = (double)colDiff / rowDiff;
            // Escape by moving away
            for (auto &d : dirs)
            {
                int nr = kingRow + d.first;
                int nc = kingRow + d.second;
                if (currKing->checkMove({nr, nc}, &board) && !inDanger(attacked, kingRow + d.first, kingCol + d.second))
                {
                    return false;
                }
            }
            // Escape by blocking
            // Down right
            if (rowDiff > 0 && colDiff > 0)
            {
                int i = 1;
                while (kingRow + i <= attackerRow)
                {
                    if (canBlock(attacked, kingRow + i, kingCol + i))
                    {
                        return false;
                    }
                    i++;
                }
            }
            // Up right
            else if (rowDiff < 0 && colDiff > 0)
            {
                int i = 1;
                while (kingRow - i >= attackerRow)
                {
                    if (canBlock(attacked, kingRow - i, kingCol + i))
                    {
                        return false;
                    }
                    i++;
                }
            }
            // Down left
            else if (rowDiff > 0 && colDiff < 0)
            {
                int i = 1;
                while (kingRow + i <= attackerRow)
                {
                    if (canBlock(attacked, kingRow + i, kingCol - i))
                    {
                        return false;
                    }
                    i++;
                }
            }
            // Up left
            else
            {
                int i = 1;
                while (kingRow - i >= attackerRow)
                {
                    if (canBlock(attacked, kingRow - i, kingCol - i))
                    {
                        return false;
                    }
                    i++;
                }
            }
        }
        // Horse
        else
        {
            for (auto &d : dirs)
            {
                int nr = kingRow + d.first;
                int nc = kingRow + d.second;
                if (currKing->checkMove({nr, nc}, &board) && !inDanger(attacked, kingRow + d.first, kingCol + d.second))
                {
                    return false;
                }
            }
        }
    }
    // 2 attackers
    else
    {
        for (auto &d : dirs)
        {
            int nr = kingRow + d.first;
            int nc = kingRow + d.second;
            if (currKing->checkMove({nr, nc}, &board) && !inDanger(attacked, kingRow + d.first, kingCol + d.second))
            {
                return false;
            }
        }
    }
    return true;
}

bool Chessgame::inStalemate()
{
    if (turn == Colour::WHITE && blackAttackingMoves.size() == 0)
    {
        return true;
    }
    else if (turn == Colour::BLACK && whiteAttackingMoves.size() == 0)
    {
        return true;
    }
    return false;
}

void Chessgame::move(string coord1, string coord2)
{
    pair<int, int> start = convertCoord(coord1);
    pair<int, int> end = convertCoord(coord2);

    Piece *piece = board.getPiece(start.first, start.second);
    if (piece == nullptr || piece->getColour() != turn)
    {
        cout << "Invalid starting position!" << endl;
        return;
    }

    if (turn == Colour::WHITE)
    {
        p1->move(start, end);
        updateAttackingMoves(Colour::WHITE);
    }
    else
    {
        p2->move(start, end);
        updateAttackingMoves(Colour::BLACK);
    }

    /*
    1 -> someone is in check
    2 -> someone is in checkmate
    3 -> stalemate
    */

    if (inCheck())
    {
        if (turn == Colour::WHITE)
        {
            cout << "Black is in check." << endl;
        }
        else
        {
            cout << "White is in check." << endl;
        }
    };

    if (inCheckmate())
    {
        if (turn == Colour::WHITE)
        {
            cout << "Checkmate! White wins!" << endl;
            sb->incrementScore(Colour::WHITE);
        }
        else
        {
            cout << "Checkmate! Black wins!" << endl;
            sb->incrementScore(Colour::BLACK);
        }
    }

    if (inStalemate())
    {
        cout << "Stalemate!" << endl;
        sb->staleMate();
    }
}