#include "piece.h"
#include "board.h"
#include "rook.h"
#include "bishop.h"
#include "king.h"
#include "queen.h"
#include "knight.h"
#include "pawn.h"
#include "level1computer.h"
#include "colour.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <vector>

using namespace std;

bool Computer1::move(Board *board, std::pair<int, int> start, std::pair<int, int> finish, char tempChar){ 
    bool isMoved = false;

    vector<vector<int>> moves;
    b->updateAttackingMoves(c,0);

    if(this->c == Colour::WHITE){
        moves = b->whiteAttackingMoves;

    } else {
        moves = b->blackAttackingMoves;
    }

    srand (time(NULL));

    int size1 = moves.size();
    int index1 = rand() % size1;
    auto a = moves[index1];

    int randomProm = rand() % 5;
    char type;

    // this is used for promotion
    for(auto a: moves){
        Piece* p = b->getPiece(a[2], a[3]);
        if(p->getType() == Type::PAWN && p->getColour() == Colour::WHITE && a[0] == 0){
            switch(randomProm){
                case 0: 
                    type = 'P';
                    break;
                case 1: 
                    type = 'R';
                    break;
                case 2: 
                    type = 'Q';
                    break;
                case 3: 
                    type = 'N';
                    break;
                case 4: 
                    type = 'B';
                    break;
            }
            b->move(make_pair(a[2], a[3]), make_pair(a[0], a[1]), type);
            return true;
        } else if(p->getType() == Type::PAWN && p->getColour() == Colour::BLACK && a[0] == 6){
            switch(randomProm){
                case 0: 
                    type = 'p';
                    break;
                case 1: 
                    type = 'r';
                    break;
                case 2: 
                    type = 'q';
                    break;
                case 3: 
                    type = 'n';
                    break;
                case 4: 
                    type = 'b';
                    break;
            }
            b->move(make_pair(a[2], a[3]), make_pair(a[0], a[1]), type);
            return true;
        }
    }

    if(a[3] && a[2]){
        isMoved = true;
    }

    return b->move(make_pair(a[2], a[3]), make_pair(a[0], a[1]), '\0');

    return isMoved; 
}   