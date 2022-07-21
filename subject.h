#ifndef SUBJECT_H
#define SUBJECT_H

#include "observer.h"
#include "piece.h"
#include <vector>

class Observer;
class Piece;

class Subject
{
    std::vector<Observer *> observers;

public:
    void attach(Observer *);
    void notifyObservers(Piece *, std::pair<int, int>);
};

#endif