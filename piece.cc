#include <piece.h>
#include <string>

using namespace std;

string Piece::getName() {}

string Piece::getColour() {}

int Piece::getPos() {}

void Piece::setPos(int x, int y) {}

void Piece::move(int r, int c, int nr, int nc) {}

bool Piece::isMoved() {}

void Piece::setMove(bool m) {}

bool Piece::isRiskyMove(int r, int c, int nr, int nc) {}

void Piece::notifyObservers() {}