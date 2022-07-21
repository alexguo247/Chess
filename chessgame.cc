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

Piece* buildPiece(char pieceType, pair<int, int> pos) {
    Piece *p;
    switch (pieceType) {
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
{
    sb = new Scoreboard();
};

Chessgame::~Chessgame() {
    delete sb;
    delete p1; 
    delete p2;
    board.clearBoard();
}

bool Chessgame::validateBoard() {


}

void Chessgame::defaultConfiguration() {
    turn = Colour::WHITE;
    whiteKing = pair<int, int>{7, 4};
    blackKing = pair<int, int>{0, 4};

    board.setup(blackAttackingMoves, whiteAttackingMoves);
}

void Chessgame::setup() {
    defaultConfiguration();
    string cmd; 
    char pieceType;
    string coord;
    pair<int, int> coordPair;
    cin >> cmd;
    bool exit = false;

    Piece *p; 

    while (!exit) {
        if (cmd == "black") {
            turn = Colour::BLACK;
        } else if (cmd == "white") {
            turn = Colour::WHITE;
        } else if (cmd == "+") {
            cin >> pieceType;
            cin >> coord;
            coordPair = convertCoord(coord);
            board.setPiece(buildPiece(pieceType, coordPair), coordPair.first, coordPair.second);
        } else if (cmd == "-") {
            cin >> coord;
            coordPair = convertCoord(coord);
            board.deletePiece(coordPair.first, coordPair.second);
        } else if (cmd == "done") {
            if (validateBoard()) {
                exit = true;
            } else {
                cout << "Board not in valid state. Can't leave setup!" << endl;
            }
        }
    }

    hasSetup = true;
}

void Chessgame::game(string player1, string player2)
{
    if (!hasSetup) {
        defaultConfiguration();
    }

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
                        whiteAttackingMoves.insert(a);
                    }
                    else
                    {
                        blackAttackingMoves.insert(a);
                    }
                }
            }
        }
    }
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
        p1->move(start, end, whiteKing);
        updateAttackingMoves(Colour::WHITE);
    } else {
        p2->move(start, end, blackKing);
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

    if (turn == Colour::WHITE) {
        turn = Colour::BLACK;
    } else {
        turn = Colour::WHITE;
    }

}
