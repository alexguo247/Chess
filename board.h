#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include "type.h"
#include "colour.h"
#include <stdbool.h>
#include "colour.h"

class Piece;

class Board
{
    std::vector<std::vector<int>> getAttackers(Colour);
    bool canBlock(Colour, int, int);
    Screen * s; 
public:
    int turn;
    std::vector<std::vector<Piece *>> grid;
    std::vector<std::vector<int>> whiteAttackingMoves;
    std::vector<std::vector<int>> blackAttackingMoves;
    Board();
    Piece *getPiece(int, int);
    void setOrCreatePiece(Piece *, int, int, bool, Type, Colour);
    bool isValid();
    Type getTypeChar(char);
    char getCharType(Piece *);
    void incrementTurn();
    void resetTurn();
    void print();
    void printDisplay();
    bool move(std::pair<int, int>, std::pair<int, int>, char); // false if error
    void deletePiece(int, int);
    void clearBoard();
    void setup();
    void updateAttackingMoves(Colour, int);
    bool validateBoard();
    std::pair<int, int> findKing(Colour);
    bool inDanger(Colour, int, int);
    bool inCheck(Colour);
    bool inCheckmate(Colour);
    bool inStalemate(Colour);
    bool causesCheck(Piece *, std::pair<int, int>, int);
    bool causesOpposingCheck(Piece *, std::pair<int, int>);
};

#endif
