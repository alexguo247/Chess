#include <piece.h>
#include <string>

using namespace std;

Type Piece::getType() { return type; }

Colour Piece::getColour() { return colour; }

int Piece::getPos() {}

void Piece::setPos(int x, int y) {}

void Piece::move(int r, int c, int nr, int nc) {}

bool Piece::isMoved() {}

void Piece::setMove(bool m) {}

bool Piece::isRiskyMove(int r, int c, int nr, int nc) {}

void Piece::notifyObservers() {}