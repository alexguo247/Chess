#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H

#include <string>
#include <iostream>
#include <vector>

#include "type.h"
#include "observer.h"
#include "piece.h"

class Piece;

class Textdisplay : public Observer
{
    std::vector<std::vector<char>> theDis;

public:
    Textdisplay();
    void defaultSetup();
    void notify(Piece *p, std::pair<int, int>);
    char getCharType(Piece *p);
    friend std::ostream &operator<<(std::ostream &out, const Textdisplay &td);
    ~Textdisplay();
};
#endif