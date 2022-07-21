#ifndef CHESSGAME_H
#define CHESSGAME_H
#include <set>
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
    set<pair<int, int>> whiteAttackingMoves;
    set<pair<int, int>> blackAttackingMoves;
    pair<int, int> blackKing;
    pair<int, int> whiteKing;
    void updateAttackingMoves(Colour);
    void defaultConfiguration();
    bool validateBoard();

public:
    Chessgame();
    ~Chessgame();
    void game(string, string);
    void move(string, string);
    void resign();
    void setup();
};

#endif;