#ifndef CHESSGAME_H
#define CHESSGAME_H
#include <string>
#include <iostream>
#include <vector>
#include "board.h"
#include "textdisplay.h"
#include "scoreboard.h"

class Player;

class Chessgame
{
    Board board;
    Player *p1;
    Player *p2;
    bool hasSetup;
    Colour turn;
    Textdisplay* td;
    Scoreboard *sb;
    std::vector<std::vector<int>> whiteAttackingMoves;
    std::vector<std::vector<int>> blackAttackingMoves;
    std::pair<int, int> findKing(Colour);
    void updateAttackingMoves(Colour);
    std::vector<std::vector<int>> getAttackers(Colour);
    bool canBlock(Colour, int, int);
    bool inDanger(Colour, int, int);
    void defaultConfiguration();
    bool validateBoard();
    void attachObservers();

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
