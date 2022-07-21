#ifndef CHESSGAME_H
#define CHESSGAME_H
#include <set>
#include <string>
#include <iostream>
#include "board.h"
#include "player.h"
#include "scoreboard.h"

class Chessgame
{
    Board board;
    Player *p1;
    Player *p2;
    bool hasSetup;
    Colour turn;
    Scoreboard *sb;
    std::set<std::pair<int, int>> whiteAttackingMoves;
    std::set<std::pair<int, int>> blackAttackingMoves;
    std::pair<int, int> blackKing;
    std::pair<int, int> whiteKing;
    void updateAttackingMoves(Colour);
    void defaultConfiguration();
    bool validateBoard();

public:
    Chessgame();
    ~Chessgame();
    void game(std::string, std::string);
    void move(std::string, std::string);
    void resign();
    void setup();
};

#endif
