#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H

#include <string>
#include <iostream>

#include "type.h"
#include "piece.h"

class Textdisplay: public Observer
{
private:
    char **theDis;

public:
    Textdisplay();
    void notify(Piece *p, std::pair<int, int>);
    char getCharType(Piece *p);
    friend std::ostream &operator<<(std::ostream &out, const Textdisplay &td);
    ~Textdisplay();
};
#endif