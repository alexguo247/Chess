#include "scoreboard.h"
#include <iostream>

using namespace std;

Scoreboard::Scoreboard() : white{0}, black{0} {}

void Scoreboard::incrementScore(Colour c)
{

    if (c == Colour::WHITE)
    {
        white++;
    }
    else if (c == Colour::BLACK)
    {
        black++;
    }
}

void Scoreboard::staleMate()
{
    black += 0.5;
    white += 0.5;
}

void Scoreboard::print()
{
    cout << endl;
    cout << "Final Score:" << endl;
    cout << "White:" << white << endl;
    cout << "Black:" << black << endl;
}
