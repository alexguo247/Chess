#include "chessgame.h"
#include "colour.h"
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

Chessgame::Chessgame() : p1{nullptr}, p2{nullptr}, turn{Colour::WHITE} {};

void Chessgame::game(string player1, string player2) {
    p1 = player1 == "human" ? new Human(&board, Colour::WHITE) : new Computer(&board, Colour::WHITE);
    p2 = player2 == "human" ? new Human(&board, Colour::BLACK) : new Computer(&board, Colour::BLACK);
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

void Chessgame::updateAttackingMoves(Colour c) {
    if (c == Colour::WHITE) {
        whiteAttackingMoves.clear();
    } else {
        blackAttackingMoves.clear();
    }

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (board.getPiece(i, j)->getColour() == c) {
               for (auto a: board.getPiece(i, j)->getAttackMoves(&board)) {
                   if (c == Colour::WHITE) {
                        whiteAttackingMoves.insert(a);
                   } else {
                        blackAttackingMoves.insert(a);
                   }
               }
            }
        }
    }

}

void Chessgame::move(string coord1, string coord2) {
    pair<int, int> start = convertCoord(coord1);
    pair<int, int> end = convertCoord(coord2);

    Piece *piece = board.getPiece(start.first, start.second);
    if (piece == nullptr || piece->getColour() != turn) {
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

    if (inCheck()) {
        if (turn == Colour::WHITE) {
            cout << "Black is in check." << endl;
        }
        else
        {
            cout << "White is in check." << endl;
        }
    };

    if (inCheckmate()) {
        if (turn == Colour::WHITE) {
            cout << "Checkmate! White wins!" << endl;
        }
        else
        {
            cout << "Checkmate! Black wins!" << endl;
        }
    }

    if (inStalemate()) {
        cout << "Stalemate!" << endl;
    }

    if (turn == Colour::WHITE) {
        turn = Colour::BLACK;
    } else {
        turn = Colour::WHITE;
    }
}