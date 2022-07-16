#include "board.h"

class Chessgame {
    Board board;
    Player p1;
    Player p2;
    Colour turn;

    public:
        void game(string, string);
        void move(string, string);
        void resign();
        void setup();
};