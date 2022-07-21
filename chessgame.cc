#include "chessgame.h"
#include "colour.h"
#include "human.h"
#include "piece.h"
#include "board.h"
#include "rook.h"
#include "bishop.h"
#include "king.h"
#include "queen.h"
#include "knight.h"
#include "pawn.h"

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

Piece *buildPiece(char pieceType, pair<int, int> pos)
{
    Piece *p;
    switch (pieceType)
    {
    case 'K':
        p = new King(Colour::WHITE, pos.first, pos.second);
    case 'R':
        p = new Rook(Colour::WHITE, pos.first, pos.second);
    case 'N':
        p = new Knight(Colour::WHITE, pos.first, pos.second);
    case 'B':
        p = new Bishop(Colour::WHITE, pos.first, pos.second);
    case 'Q':
        p = new Queen(Colour::WHITE, pos.first, pos.second);
    case 'P':
        p = new Pawn(Colour::WHITE, pos.first, pos.second);
    case 'k':
        p = new King(Colour::BLACK, pos.first, pos.second);
    case 'r':
        p = new Rook(Colour::BLACK, pos.first, pos.second);
    case 'n':
        p = new Knight(Colour::BLACK, pos.first, pos.second);
    case 'b':
        p = new Bishop(Colour::BLACK, pos.first, pos.second);
    case 'q':
        p = new Queen(Colour::BLACK, pos.first, pos.second);
    case 'p':
        p = new Pawn(Colour::BLACK, pos.first, pos.second);
    }
    return p;
}

Chessgame::Chessgame() : p1{nullptr}, p2{nullptr}
pair<int, int> Chessgame::findKing(Colour c) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (board.getPiece(i, j)->getType() == Type::KING && board.getPiece(i, j)->getColour() == c) {
                return pair<int, int>{i, j};
            }
        }
    }
}

Chessgame::Chessgame() : p1{nullptr}, p2{nullptr}  
{
    sb = new Scoreboard();
    td = new Textdisplay();
};

Chessgame::~Chessgame()
{
    delete sb;
    delete p1;
    delete td;
    delete p2;
    board.clearBoard();
}

bool Chessgame::validateBoard()
{
    bool valid = true;
    int whiteKingCount = 0;
    int blackKingCount = 0;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (i == 0 || i == 7)
            {
                if (board.getPiece(i, j)->getType() == Type::PAWN)
                {
                    valid = false;
                }
            }
            if (board.getPiece(i, j)->getType() == Type::KING)
            {
                if (board.getPiece(i, j)->getColour() == Colour::BLACK)
                {
                    if (inDanger(Colour::BLACK, i, j))
                    {
                        valid = false;
                    }
                    blackKingCount++;
                }
                else
                {
                    if (inDanger(Colour::WHITE, i, j))
                    {
                        valid = false;
                    }
                    whiteKingCount++;
                }
            }
        }
    }
    if (whiteKingCount != 1 || blackKingCount != 1)
    {
        valid = false;
    }
    return valid;

void Chessgame::attachObservers() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            board.getPiece(i, j)->attach(td);
        }
    }
}

void Chessgame::defaultConfiguration()
{
    turn = Colour::WHITE;
    board.setup(blackAttackingMoves, whiteAttackingMoves);
}

void Chessgame::setup()
{
    defaultConfiguration();
    string cmd;
    char pieceType;
    string coord;
    pair<int, int> coordPair;
    cin >> cmd;
    bool exit = false;

    Piece *p;

    while (!exit)
    {
        if (cmd == "black")
        {
            turn = Colour::BLACK;
        }
        else if (cmd == "white")
        {
            turn = Colour::WHITE;
        }
        else if (cmd == "+")
        {
            cin >> pieceType;
            cin >> coord;
            coordPair = convertCoord(coord);
            board.setPiece(buildPiece(pieceType, coordPair), coordPair.first, coordPair.second);
        }
        else if (cmd == "-")
        {
            cin >> coord;
            coordPair = convertCoord(coord);
            board.deletePiece(coordPair.first, coordPair.second);
        }
        else if (cmd == "done")
        {
            if (validateBoard())
            {
                exit = true;
            }
            else
            {
                cout << "Board not in valid state. Can't leave setup!" << endl;
            }
        }
    }

    hasSetup = true;
}

void Chessgame::game(string player1, string player2)
{
    if (!hasSetup)
    {
        defaultConfiguration();
    }
    td->setupFromBoard(&board);
    attachObservers();

    p1 = player1 == "human" ? new Human(&board, Colour::WHITE) : new Computer(&board, Colour::WHITE);
    p2 = player2 == "human" ? new Human(&board, Colour::BLACK) : new Computer(&board, Colour::BLACK);
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
    hasSetup = false;
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

    if (turn == Colour::WHITE) {
        p1->move(start, end);
        updateAttackingMoves(Colour::WHITE);
    } else {
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
        hasSetup = false;
    }

    if (inStalemate())
    {
        cout << "Stalemate!" << endl;
        sb->staleMate();
        hasSetup = false;
    }

    if (turn == Colour::WHITE)
    {
        turn = Colour::BLACK;
    }
    else
    {
        turn = Colour::WHITE;
    }
}
