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
    vector<vector<int>> whiteAttackingMoves;
    vector<vector<int>> blackAttackingMoves;
    Scoreboard *sb;
    std::vector<std::vector<int>> whiteAttackingMoves;
    std::vector<std::vector<int>> blackAttackingMoves;
    std::pair<int, int> blackKing;
    std::pair<int, int> whiteKing;
    void updateAttackingMoves(Colour);
    vector<vector<int>> getAttackers(Colour);
    bool canBlock(Colour, int, int);
    bool inDanger(Colour, int, int);
    void defaultConfiguration();
    bool validateBoard();

public:
    Chessgame();
    ~Chessgame();
    void game(std::string, std::string);
    void move(std::string, std::string);
    void resign();
    void setup();
    bool inCheck();
    bool inCheckmate();
    bool inStalemate();
};

#endif
