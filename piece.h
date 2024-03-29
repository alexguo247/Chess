#ifndef PIECE_H
#define PIECE_H

#include "colour.h"
#include "type.h"
#include <vector>
#include <string>

class Board;

class Piece
{
protected:
    Colour colour;
    Type type;
    int row;
    int col;
    bool hasMoved;

public:
    Piece(Colour, Type, int, int, bool);
    virtual ~Piece();
    Colour getColour();                                       // return the colour of the piece
    Type getType();                                           // return the type of the piece
    std::pair<int, int> getPos();                             // return the position of the piece
    void setPos(int, int);                                    // set the position of the piece
    virtual bool checkMove(std::pair<int, int>, Board &) = 0; // check if move is valid
    virtual std::vector<std::vector<int>> getAttackMoves(Board &, int) = 0;
    virtual bool getHasMoved();
};
#endif
