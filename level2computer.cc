#include "piece.h"
#include "board.h"
#include "rook.h"
#include "bishop.h"
#include "king.h"
#include "queen.h"
#include "knight.h"
#include "pawn.h"
#include "level2computer.h"
#include "colour.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <vector>
#include "piece.h"

using namespace std;

bool Computer2::move(Board *board, std::pair<int, int> start, std::pair<int, int> finish, char tempChar){ 

//perfers capturing moves and checks over other moves

    bool isMoved = false;

    vector<vector<int>> moves;
    b->updateAttackingMoves(c,0);

    if(this->c == Colour::WHITE){
        moves = b->whiteAttackingMoves;

    } else {
        moves = b->blackAttackingMoves;
    }


    //check 
    for(auto a: moves){
        Piece* p = b->getPiece(a[2], a[3]);
        if(b->causesOpposingCheck(p, make_pair(a[0], a[1]))){
            b->move(make_pair(a[2], a[3]), make_pair(a[0], a[1]), '\0');
            return true;
        }
    }

    //for each attacking peice, check if it's occupied - capture
    for(auto a: moves){
        if((b->getPiece(a[0], a[1])) != nullptr){
            b->move(make_pair(a[2], a[3]), make_pair(a[0], a[1]), '\0');
            return true;
        }
    }

    srand (time(NULL));

    int size1 = moves.size();
    int index1 = rand() % size1;

    auto a = moves[index1];

    
    if(a[3] && a[2]){
        isMoved = true;
    }

    b->move(make_pair(a[2], a[3]), make_pair(a[0], a[1]), '\0');

    return isMoved; 
        

}   