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
Piece* Piece::operator=(const Piece *p2) {
    cout << "HI" << endl;
    this->colour = p2->colour;
    this->type = p2->type;
    this->row = p2->row;
    this->col = p2->col;
    return this;
}