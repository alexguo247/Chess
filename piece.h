#ifndef PIECE_H
#define PIECE_H

#include "colour.h"
#include "type.h"

#include <string>

class Board;

class Piece
{
protected:
    Colour colour;
    Type type;
    int row;
    int col;

public:
    Piece(Colour, Type, int, int);
    virtual ~Piece();
    virtual Colour getColour();                               // return the colour of the piece
    virtual Type getType();                                   // return the type of the piece
    virtual std::pair<int, int> getPos();                     // return the position of the piece
    virtual void setPos(int, int);                            // set the position of the piece
    virtual void move(std::pair<int, int>, Board *);          // move the peice from old location to the new location
    virtual bool checkMove(std::pair<int, int>, Board *) = 0; // check if move is valid
    virtual std::vector<std::vector<int>> getAttackMoves(Board *) = 0;
};
#endif
