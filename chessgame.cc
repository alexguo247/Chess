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
#include <sstream>
#include <cmath>
#include <vector>

using namespace std;

pair<int, int> convertCoord(string coord)
{
    if (coord.length() == 0)
    {
        return make_pair(-1, -1);
    }

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

Chessgame::Chessgame() : p1{nullptr}, p2{nullptr}
{
    sb = new Scoreboard();
    s = new Screen(640, 640);
};

Chessgame::~Chessgame()
{
    delete sb;
    delete s;
    board.clearBoard();
    delete p1;
    delete p2;
}

void Chessgame::defaultConfiguration()
{
    turn = Colour::WHITE;
    board.setup();
    board.updateAttackingMoves(turn, 0);
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
        board.clearBoard();
    }

    string line;
    string cmd;
    string coord;
    pair<int, int> coordPair;
    char pieceType;
    turn = Colour::WHITE;
    bool exit = false;

    while (!exit)
    {
        getline(cin, line);
        stringstream input(line);
        input >> cmd;
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
            input >> pieceType;
            input >> coord;
            coordPair = convertCoord(coord);
            board.setOrCreatePiece(nullptr, coordPair.first, coordPair.second, true, board.getTypeChar(pieceType), isupper(pieceType) ? Colour::WHITE : Colour::BLACK);
            board.print();
            board.printDisplay(s);
            board.updateAttackingMoves(turn, 0);
        }
        else if (cmd == "-")
        {
            input >> coord;
            coordPair = convertCoord(coord);
            board.deletePiece(coordPair.first, coordPair.second);
            board.print();
            board.printDisplay(s);
            board.updateAttackingMoves(turn, 0);
        }
        else if (cmd == "done")
        {
            if (board.validateBoard())
            {
                exit = true;
                break;
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
    if (gameIsRunning)
    {
        cout << "Game is already running." << endl;
        return;
    }

    // if (!hasSetup)
    // {
    //     defaultConfiguration();
    // }

    hasSetup = false;
    gameIsRunning = true;
    board.resetTurn(); // turn number

    if (player1 == "human")
    {
        p1 = new Human(&board, Colour::WHITE);
    }
    else if (player1 == "computer1")
    {
        p1 = new Computer1(&board, Colour::WHITE);
    }
    else if (player1 == "computer2")
    {
        p1 = new Computer2(&board, Colour::WHITE);
    }
    else if (player1 == "computer3")
    {
        p1 = new Computer3(&board, Colour::WHITE);
    }
    else if (player1 == "computer4")
    {
        p1 = new Computer4(&board, Colour::WHITE);
    }
    else
    {
        cout << "Invalid player 1 type!" << endl;
        return;
    }

    if (player2 == "human")
    {
        p2 = new Human(&board, Colour::BLACK);
    }
    else if (player2 == "computer1")
    {
        p2 = new Computer1(&board, Colour::BLACK);
    }
    else if (player2 == "computer2")
    {
        p2 = new Computer2(&board, Colour::BLACK);
    }
    else if (player2 == "computer3")
    {
        p2 = new Computer3(&board, Colour::BLACK);
    }
    else if (player2 == "computer4")
    {
        p2 = new Computer4(&board, Colour::BLACK);
    }
    else
    {
        cout << "Invalid player 2 type!" << endl;
        return;
    }

    board.print();
    board.printDisplay(s);
}

void Chessgame::resign()
{
    if (!gameIsRunning)
    {
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

void Chessgame::move(string coord1, string coord2, char promotion)
{
    if (!gameIsRunning)
    {
        cout << "Can't move. No active game is running." << endl;
        return;
    }

    pair<int, int> start = convertCoord(coord1);
    pair<int, int> end = convertCoord(coord2);

    if (coord1.length() != 0 && coord2.length() != 0)
    {
        Piece *piece = board.getPiece(start.first, start.second);

        if (piece == nullptr)
        {
            cout << "No piece to move at that square! Move again." << endl;
            return;
        }

        if (piece->getColour() != turn)
        {
            cout << "Moving piece of opposite colour is not allowed! Move again." << endl;
            return;
        }
    }

    if (turn == Colour::WHITE)
    {
        if (!p1->move(&board, start, end, promotion))
        {
            return;
        }
    }
    else
    {
        if (!p2->move(&board, start, end, promotion))
        {
            return;
        }
    }

    board.incrementTurn();
    board.print();
    board.printDisplay(s);
    board.updateAttackingMoves(turn, 0);
    if (board.inCheck(turn))
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
    if (board.inCheckmate(turn))
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
    if (board.inStalemate(turn))
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
