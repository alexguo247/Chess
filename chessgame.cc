#include "chessgame.h"
#include "colour.h"
#include <iostream>

using namespace std;

// AGUO ADD A convertCoord func plzzzzzzzzzzzzzz
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

Chessgame::Chessgame() : p1{nullptr}, p2{nullptr}, turn{Colour::WHITE} {};

void Chessgame::game(string player1, string player2)
{
    p1 = player1 == "human" ? new Human(Colour::WHITE) : new Computer(Colour::WHITE);
    p2 = player2 == "human" ? new Human(Colour::BLACK) : new Computer(Colour::BLACK);
    board.setup(blackAttackingMoves, whiteAttackingMoves, blackKing, whiteKing);
}

void Chessgame::resign()
{
    if (turn == Colour::WHITE)
    {
        cout << "Black wins!" << endl;
    }
    else
    {
        cout << "White wins!" << endl;
    }
}

void Chessgame::move(string coord1, string coord2)
{
    pair<int, int> start = convertCoord(coord1);
    pair<int, int> end = convertCoord(coord2);

    int res = turn == Colour::WHITE ? p1->move(start, end) : p2->move(start, end);

    /*
    1 -> someone is in check
    2 -> someone is in checkmate
    3 -> stalemate
    4 -> move was invalid
    */

    if (res == 1)
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

    if (res == 2)
    {
        if (turn == Colour::WHITE)
        {
            cout << "Checkmate! White wins!" << endl;
        }
        else
        {
            cout << "Checkmate! Black wins!" << endl;
        }
    }

    if (res == 3)
    {
        cout << "Stalemate!" << endl;
    }

    if (res == 4)
    {
        cout << "Invalid move!" << endl;
    }
}