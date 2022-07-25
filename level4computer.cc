#include "piece.h"
#include "board.h"
#include "rook.h"
#include "bishop.h"
#include "king.h"
#include "queen.h"
#include "knight.h"
#include "pawn.h"
#include "level4computer.h"
#include "colour.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <vector>
#include "piece.h"
#include "type.h"

using namespace std;

bool computer4::move(Board *board, std::pair<int, int> start, std::pair<int, int> finish, char tempChar){ 
    
    bool isMoved = false;

    vector<vector<int>> moves;
    vector<vector<int>> opposingMoves;
    Colour opposingColour = (c == Colour::WHITE) ? Colour::BLACK : Colour::WHITE;
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

    // here we want to value checkmate as our primary move and we'll also focus on moving the knight and 
    // bishop and pawn so we can keep our values pieces such as king queen and rook 

    // Here we are valuing a checkmate of the opposing colour and will always try to make that 
    // move before anything else
    for(auto a: moves){
        Piece* p = b->getPiece(a[2], a[3]);
        if(b->causesOpposingCheck(p, make_pair(a[0], a[1]))){
            if(b->inCheckmate(opposingColour)){
                b->move(make_pair(a[2], a[3]), make_pair(a[0], a[1]), '\0');
                return true;
            }
        }
    }

    //move any of your pieces that are going to be captured
    for(auto a: opposingMoves){
        for(auto c: moves){
            if((a[0] == c[2]) && (a[1] == c[3])){
                b->move(make_pair(c[2], c[3]), make_pair(c[0], c[1]), '\0');
                return true; 
            }
        }
    }

    //check if check is possible with bishop or knight so we can cover more area 
    for(auto a: moves){
        Piece* p = b->getPiece(a[2], a[3]);
        Piece * temp = b->getPiece(a[2], a[3]);

        if(temp->getType() == Type::BISHOP || 
                temp->getType() == Type::KNIGHT)
            {

                if(b->causesOpposingCheck(p, make_pair(a[0], a[1]))){
                    b->move(make_pair(a[2], a[3]), make_pair(a[0], a[1]), '\0');
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
    //IN ADDITION: we are trying to further our knight and bishop so we check if any of these
    // pieces can make a capture
    for(auto a: moves){
        if((b->getPiece(a[0], a[1])) != nullptr){
            if(b->getPiece(a[0], a[1])->getType() == Type::BISHOP || 
                b->getPiece(a[0], a[1])->getType() == Type::KNIGHT)
            {
                // perfer the move with bishop and knight over others
                b->move(make_pair(a[2], a[3]), make_pair(a[0], a[1]), '\0');
                return true;
            }
        }
    }

    // if bishop or knight dont have capture moves, continue with other piece
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