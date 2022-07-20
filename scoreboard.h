#ifndef __SCOREBOARD_H__
#define __SCOREBOARD_H__

#include <string>
#include "colour.h"

class Scoreboard
{
    float white;
    float black;

public:
    Scoreboard();
    void print();
    void incrementScore(Colour c);
    void staleMate();
};

#endif