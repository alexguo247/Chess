#include "piece.h"

class Observer {
    public:
        virtual void notify(Piece *, std::pair<int, int>) = 0;
};