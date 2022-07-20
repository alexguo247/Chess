#include "piece.h"
#include <vector>
#include <stdbool.h>
#include <set>

class Board
{
    std::vector<std::vector<Piece *>> grid;

public:
    Piece *getPiece(int, int);
    void setPiece(Piece *, int, int);
    bool isValid();
    void setup(std::set<pair<int, int>> &, std::set<pair<int, int>> &, pair<int, int> &, pair<int, int> &);
};