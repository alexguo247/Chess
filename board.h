#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <stdbool.h>
#include "colour.h"

class Piece;

class Board
{
    std::vector<std::vector<int>> whiteAttackingMoves;
    std::vector<std::vector<int>> blackAttackingMoves;
    std::vector<std::vector<int>> getAttackers(Colour);
    std::pair<int, int> findKing(Colour);
    bool canBlock(Colour, int, int);

public:
    std::vector<std::vector<Piece *>> grid;
    Board();
    Piece *getPiece(int, int);
    void setPiece(Piece *, int, int);
    bool isValid();
    void print();
    void deletePiece(int, int);
    void clearBoard();
    void setup();
    void updateAttackingMoves();
    bool validateBoard();
    bool inDanger(Colour, int, int);
    bool inCheck(Colour);
    bool inCheckmate(Colour);
    bool inStalemate(Colour);
};

#endif
