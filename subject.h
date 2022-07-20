#include "observer.h"
#include <vector>

class Subject {
    std::vector<Observer *> observers;
    public:
        void attach(Observer *);
        void notifyObservers(Piece *, std::pair<int, int>);
};