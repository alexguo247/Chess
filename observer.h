#ifndef OBSERVER_H
#define OBSERVER_H

#include "piece.h"

class Observer
{
public:
    virtual void notify(Piece *, std::pair<int, int>) = 0;
};

#endif;