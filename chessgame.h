#ifndef CHESSGAME_H
#define CHESSGAME_H
#include <string>
#include <iostream>
#include <vector>
#include "board.h"
#include "scoreboard.h"

class Player;

class Chessgame
{
    Board board;
    Player *p1;
    Player *p2;
    bool hasSetup;
    bool gameIsRunning;
    Colour turn;
    Scoreboard *sb;
    void defaultConfiguration();

public:
    Chessgame();
    ~Chessgame();
    void game(std::string, std::string);
    void move(std::string, std::string, char);
    void resign();
    void setup();
};

#endif
