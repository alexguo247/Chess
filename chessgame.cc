#include "chessgame.h"
#include "colour.h"

using namespace std;

Chessgame::Chessgame() : p1{nullptr}, p2{nullptr}, turn{Colour::WHITE} {};

void Chessgame::game(string player1, string player2) {
    p1 = player1 == "human" ? new Human(Colour::WHITE) : new Computer(Colour::WHITE);
    p2 = player2 == "human" ? new Human(Colour::BLACK) : new Computer(Colour::BLACK);
    board.setup();
}

void Chessgame::
