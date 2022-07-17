#include "piece.h"
#include <vector>
#include <stdbool.h>

class Board {
    std::vector<std::vector<Piece *>> grid;
    public:
        Piece* getPiece(int, int);
        void setPiece(Piece*, int, int);
        bool isValid(); 
};