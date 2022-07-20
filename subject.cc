#include "subject.h"
#include "observer.h"

using namespace std;

void Subject::attach(Observer *o) {
    observers.push_back(o);
};

void Subject::notifyObservers(Piece *p, pair<int, int> old) {
    for (int i = 0; i < observers.size(); i++) {
        observers[i]->notify(p, old);
    }
};
