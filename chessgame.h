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
    Colour turn;
    vector<vector<int>> whiteAttackingMoves;
    vector<vector<int>> blackAttackingMoves;
    Scoreboard *sb;
    pair<int, int> blackKing;
    pair<int, int> whiteKing;
    void updateAttackingMoves(Colour);
    vector<vector<int>> getAttackers(Colour);
    bool canBlock(Colour, int, int);
    bool inDanger(Colour, int, int);

public:
    Chessgame();
    void game(string, string);
    void move(string, string);
    void resign();
    void setup();
    bool inCheck();
    bool inCheckmate();
    bool inStalemate();
};
