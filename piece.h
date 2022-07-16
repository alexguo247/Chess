#ifndef PIECE_H
#define PIECE_H

#include <string>
#include <color.h>
#include <type.h>

class Piece
{
protected:
    Color colour;
    Type type;
    int row;
    int col;
    bool isMoved;

public:
    Piece(Color c, Type t) : colour{c}, type{t} {}
    virtual std::string getName();         // return the name of the piece
    virtual std::string getColour();       // return the colour of the piece
    virtual int getPos();                  // return the position of the piece
    virtual void setPos(int, int);         // set the position of the piece
    virtual void move(int, int, int, int); // move the peice from old location to the new location
    virtual bool isMoved();                // return if the piece was moved
    virtual void setMove(bool);            // set isMoved to true
    // virtual bool validMove() = 0; // check if move is valid
    virtual bool isRiskyMove(int, int, int, int);   // check if this is a risky move
    virtual bool checkMove(int, int, int, int) = 0; // check if move is valid
    void notifyObservers();
};
#endif
