#include "piece.h"
#include "board.h"
#include "rook.h"
#include "bishop.h"
#include "king.h"
#include "queen.h"
#include "knight.h"
#include "pawn.h"
#include "level3computer.h"
#include "colour.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <vector>
#include "piece.h"

using namespace std;

bool computer3::move(Board *board, std::pair<int, int> start, std::pair<int, int> finish, char tempChar){ 

//perfers capturing moves and checks over other moves
    bool isMoved = false;

    vector<vector<int>> moves;
    vector<vector<int>> opposingMoves;
    b->updateAttackingMoves(c,0);

    if(this->c == Colour::WHITE){
        moves = b->whiteAttackingMoves;

    } else {
        moves = b->blackAttackingMoves;
    }

    if(this->c == Colour::WHITE){
        opposingMoves = b->blackAttackingMoves;

    } else {
        opposingMoves = b->whiteAttackingMoves;
    }

// 0 1 -> end row col
// 2 3 -> start row col 

    //move any of your pieces that are going to be captured
    for(auto a: opposingMoves){
        for(auto c: moves){
            if((a[0] == c[2]) && (a[1] == c[3])){
                b->move(make_pair(c[2], c[3]), make_pair(c[0], c[1]), '\0');
                return true; 
            }
        }
    }

    //check if check is possible
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

    int size2 = moves[index1].size();
    int index2 = rand() & size2;

    auto a = moves[index1];

    
    if(a[3] && a[2]){
        isMoved = true;
    }

    b->move(make_pair(a[2], a[3]), make_pair(a[0], a[1]), '\0');

    return isMoved; 
        

}   