#ifndef OBSERVER_H
#define OBSERVER_H

#include "piece.h"
class Piece;

class Observer
{
public:
    virtual void notify(Piece *, std::pair<int, int>) = 0;
    virtual ~Observer() = default;
};

#endif