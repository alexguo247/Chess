#include "subject.h"
#include "observer.h"
#include <iostream>

using namespace std;

void Subject::attach(Observer *o) {
    observers.push_back(o);
};

void Subject::notifyObservers(Piece *p, pair<int, int> old) {
    cout << "NOTIFY" << endl;
    cout << observers.size() << endl;
    for (int i = 0; i < observers.size(); i++) {
        observers[i]->notify(p, old);
    }
};
