#include "piece.h"
#include "board.h"
#include <string>
#include <iostream>

using namespace std;

Type Piece::getType() { return type; }

Colour Piece::getColour() { return colour; }

Piece::Piece(Colour c, Type t, int row, int col): colour{c}, type{t}, row{row}, col{col} {};

pair<int, int> Piece::getPos() { return pair<int, int>{row, col}; }

Piece::~Piece() {};

void Piece::setPos(int x, int y) {
    row = x;
    col = y;
}

void Piece::move(pair<int, int> end, Board *b) {
    cout << "PIECE MOVING" << endl;
    pair<int, int> old = pair<int, int> {row, col};

    cout << observers.size() << endl;
    b->setPiece(this, end.first, end.second);
    cout << "1 " << observers.size() << endl;
    setPos(end.first, end.second);
    cout << "2 " << observers.size() << endl;
    b->setPiece(nullptr, old.first, old.second);
    cout << "3 " << observers.size() << endl;
    notifyObservers(this, old);
}