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

bool Computer3::move(Board *board, std::pair<int, int> start, std::pair<int, int> finish, char tempChar){ 

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

cout << "here 1" << endl;

    //move any of your pieces that are going to be captured
    for(auto a: opposingMoves){
        for(auto c: moves){
cout << "here 2" << endl;

            // cout << "inside here1" << endl;
            if((a[0] == c[2]) && (a[1] == c[3])){
cout << "here 2.5" << endl;

                b->move(make_pair(c[2], c[3]), make_pair(c[0], c[1]), '\0');
                return true; 
            }
        }
    }

cout << "here 3" << endl;


    //check if check is possible
    for(auto a: moves){
        Piece* p = b->getPiece(a[2], a[3]);
            // cout << "inside here2" << endl;
cout << "here 4" << endl;

        if(b->causesOpposingCheck(p, make_pair(a[0], a[1]))){
cout << "here 5" << endl;

            b->move(make_pair(a[2], a[3]), make_pair(a[0], a[1]), '\0');
            return true;
        }
    }

cout << "here 6" << endl;

    //for each attacking peice, check if it's occupied - capture
    for(auto a: moves){
        if((b->getPiece(a[0], a[1])) != nullptr){
            // cout << "inside here3" << endl;
cout << "here 7" << endl;

            b->move(make_pair(a[2], a[3]), make_pair(a[0], a[1]), '\0');
            return true;
        }
    }

cout << "here 8" << endl;

    srand (time(NULL));

    int size1 = moves.size();
    int index1 = rand() % size1;
    auto a = moves[index1];
    
cout << "here 9 : " << a[0] << a[1] << " " << a[2] << a[3] << endl;

    if(a[3] && a[2]){
        isMoved = true;
    }

cout << "here 10" << endl;

// 0 1 -> end row col
// 2 3 -> start row col 

    return b->move(make_pair(a[2], a[3]), make_pair(a[0], a[1]), '\0');

cout << "here 11" << endl;

    // return isMoved; 
        

}   