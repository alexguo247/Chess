#include "colour.h"

class Scoreboard {
    int p1Score;
    int p2Score;

    public:
        Scoreboard();
        void print();
        void incrementScore(Colour);
};