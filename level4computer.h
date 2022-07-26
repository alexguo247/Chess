#ifndef COMPUTER4_H
#define COMPUTER4_H
#include "player.h"
#include "board.h"
#include <vector>

class Computer4 : public Player
{
    std::vector<std::vector<int>> startingMoves; 
    int whiteMoves; 
    int blackMoves; 
    int colourNum;
public:
    Computer4(Board *b, Colour c);
    bool move(Board *board, std::pair<int, int>, std::pair<int, int>, char) override;
};

#endif

