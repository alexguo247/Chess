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
#include <vector>

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

pair<int, int> Chessgame::findKing(Colour c)
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (board.getPiece(i, j) != nullptr && board.getPiece(i, j)->getType() == Type::KING && board.getPiece(i, j)->getColour() == c)
            {
                return pair<int, int>{i, j};
            }
        }
    }
    return pair<int, int>{-1, -1};
}

Chessgame::Chessgame() : p1{nullptr}, p2{nullptr}
{
    sb = new Scoreboard();
};

Chessgame::~Chessgame()
{
    delete sb;
    delete p1;
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
            if (board.getPiece(i, j) == nullptr) {
                continue;
            }

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
}

void Chessgame::defaultConfiguration()
{
    turn = Colour::WHITE;
    board.setup();
    updateAttackingMoves();
}

void Chessgame::setup()
{
    if (gameIsRunning)
    {
        cout << "Cannot enter setup mode while game is running!" << endl;
        return;
    }

    // if board has not been setup before use default configuration
    if (!hasSetup)
    {
        defaultConfiguration();
    }

    string cmd;
    char pieceType;
    string coord;
    pair<int, int> coordPair;
    cin >> cmd;
    bool exit = false;

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
            board.setOrCreatePiece(nullptr, coordPair.first, coordPair.second, true, board.getTypeChar(pieceType), isupper(pieceType) ? Colour::WHITE : Colour::BLACK);
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
                break; 
            }
            else
            {
                cout << "Board not in valid state. Can't leave setup!" << endl;
            }
        }
        cin >> cmd;
    }

    hasSetup = true;
    board.print();
}

void Chessgame::game(string player1, string player2)
{
    if (!hasSetup)
    {
        defaultConfiguration();
    }

    hasSetup = false;
    gameIsRunning = true;

    if (player1 == "human") {
        p1 = new Human(&board, Colour::WHITE);
    } else {
        cout << "Invalid player 1 type!" << endl;
        return;
    }

    if (player2 == "human") {
        p2 = new Human(&board, Colour::BLACK);
    } else {
        cout << "Invalid player 2 type!" << endl;
        return;
    }

    board.print();
}

void Chessgame::resign()
{
    if (!gameIsRunning) {
        cout << "Can't resign, game has not started!" << endl;
        return;
    }

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

    gameIsRunning = false;
}

void Chessgame::updateAttackingMoves()
{
    whiteAttackingMoves.clear();
    blackAttackingMoves.clear();
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (board.getPiece(i, j) == nullptr)
            {
                continue;
            }

            Colour c = board.getPiece(i, j)->getColour();
            vector<vector<int>> attackMoves = board.getPiece(i, j)->getAttackMoves(board);

            for (auto a : attackMoves)
            {
                if (c == Colour::WHITE)
                {
                    whiteAttackingMoves.push_back(a);
                }
                else
                {
                    blackAttackingMoves.push_back(a);
                }
            }
        }
    }
}

bool Chessgame::inCheck()
{
    Colour attacked = (turn == Colour::WHITE) ? Colour::BLACK : Colour::WHITE;
    pair<int, int> kingCoords = findKing(attacked);
    int kingRow = kingCoords.first;
    int kingCol = kingCoords.second;
    if (inDanger(attacked, kingRow, kingCol) && !inCheckmate())
    {
        return true;
    }
    return false;
}

vector<vector<int>> Chessgame::getAttackers(Colour c)
{
    vector<vector<int>> attackers;
    pair<int, int> kingCoords = findKing(c);
    int kingRow = kingCoords.first;
    int kingCol = kingCoords.second;
    if (c == Colour::BLACK)
    {
        for (auto move : whiteAttackingMoves)
        {
            if (move[0] == kingRow && move[1] == kingCol)
            {
                attackers.push_back(move);
            }
        }
    }
    else
    {
        for (auto move : blackAttackingMoves)
        {
            if (move[0] == kingRow && move[1] == kingCol)
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
            if (move[0] == row && move[1] == col && board.getPiece(move[2], move[3])->getType() != Type::KING)
            {
                return true;
            }
        }
    }
    else
    {
        for (auto move : whiteAttackingMoves)
        {
            if (move[0] == row && move[1] == col && board.getPiece(move[2], move[3])->getType() != Type::KING)
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
    pair<int, int> kingCoords = findKing(attacked);
    int kingRow = kingCoords.first;
    int kingCol = kingCoords.second;
    Piece *currKing = board.getPiece(kingRow, kingCol);
    bool isCheckmate = true;
    // No attackers
    if (attackers.size() == 0)
    {
        isCheckmate = false;
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
                if (currKing->checkMove({nr, nc}, board) && !inDanger(attacked, kingRow + d.first, kingCol + d.second))
                {
                    isCheckmate = false;
                }
            }
            // Escape by blocking
            if (colDiff > 1)
            {
                for (int i = attackerCol; i > kingCol; i--)
                {
                    if (canBlock(attacked, attackerRow, i))
                    {
                        isCheckmate = false;
                    }
                }
            }
            else
            {
                for (int i = attackerCol; i < kingCol; i++)
                {
                    if (canBlock(attacked, attackerRow, i))
                    {
                        isCheckmate = false;
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
                if (currKing->checkMove({nr, nc}, board) && !inDanger(attacked, kingRow + d.first, kingCol + d.second))
                {
                    isCheckmate = false;
                }
            }
            // Escape by blocking
            if (rowDiff > 1)
            {
                for (int i = attackerRow; i > kingRow; i--)
                {
                    if (canBlock(attacked, i, attackerCol))
                    {
                        isCheckmate = false;
                    }
                }
            }
            else
            {
                for (int i = attackerRow; i < kingRow; i++)
                {
                    if (canBlock(attacked, i, attackerCol))
                    {
                        isCheckmate = false;
                    }
                }
            }
        }
        // Same diagonal (bishop / queen / pawn)
        else if (abs((double)(colDiff) / (rowDiff)) == 1.0)
        {
            // Escape by moving away
            for (auto &d : dirs)
            {
                int nr = kingRow + d.first;
                int nc = kingRow + d.second;
                if (currKing->checkMove({nr, nc}, board) && !inDanger(attacked, kingRow + d.first, kingCol + d.second))
                {
                    isCheckmate = false;
                }
            }
            // Escape by blocking
            // Down right
            if (rowDiff > 1 && colDiff > 1)
            {
                int i = 1;
                while (kingRow + i <= attackerRow)
                {
                    if (canBlock(attacked, kingRow + i, kingCol + i))
                    {
                        isCheckmate = false;
                    }
                    i++;
                }
            }
            // Up right
            else if (rowDiff < 1 && colDiff > 1)
            {
                int i = 1;
                while (kingRow - i >= attackerRow)
                {
                    if (canBlock(attacked, kingRow - i, kingCol + i))
                    {
                        isCheckmate = false;
                    }
                    i++;
                }
            }
            // Down left
            else if (rowDiff > 1 && colDiff < 1)
            {
                int i = 1;
                while (kingRow + i <= attackerRow)
                {
                    if (canBlock(attacked, kingRow + i, kingCol - i))
                    {
                        isCheckmate = false;
                    }
                    i++;
                }
            }
            // Up left
            else if (rowDiff < 1 && colDiff < 1)
            {
                int i = 1;
                while (kingRow - i >= attackerRow)
                {
                    if (canBlock(attacked, kingRow - i, kingCol - i))
                    {
                        isCheckmate = false;
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
                if (currKing->checkMove({nr, nc}, board) && !inDanger(attacked, kingRow + d.first, kingCol + d.second))
                {
                    isCheckmate = false;
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
            if (currKing->checkMove({nr, nc}, board) && !inDanger(attacked, kingRow + d.first, kingCol + d.second))
            {
                isCheckmate = false;
            }
        }
    }
    return isCheckmate;
}

bool Chessgame::inStalemate()
{
    if (turn == Colour::WHITE && blackAttackingMoves.size() == 0 && !inCheck())
    {

        return true;
    }
    else if (turn == Colour::BLACK && whiteAttackingMoves.size() == 0 && !inCheck())
    {
        return true;
    }
    return false;
}

void Chessgame::move(string coord1, string coord2, char promotion)
{
    pair<int, int> start = convertCoord(coord1);
    pair<int, int> end = convertCoord(coord2);

    Piece *piece = board.getPiece(start.first, start.second);
    if (piece == nullptr) {
        cout << "No piece to move at that square! Move again." << endl;
        return;
    }

    if (piece ->getColour() != turn) {
        cout << "Moving piece of opposite colour is not allowed! Move again." << endl;
        return;
    }

    if (turn == Colour::WHITE)
    {
        p1->move(&board, start, end, promotion);
    }
    else
    {
        p2->move(&board, start, end, promotion);
    }

    board.print();
    this->updateAttackingMoves();

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
        gameIsRunning = false;
        return;
    }

    if (inStalemate())
    {
        cout << "Stalemate!" << endl;
        sb->staleMate();
        gameIsRunning = false;
        return;
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

void Chessgame::printScoreboard()
{
    sb->print();
}