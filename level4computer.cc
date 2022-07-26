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

Computer4::Computer4(Board *b, Colour c): Player(b,c), blackMoves(0), whiteMoves(0) {
    if(c == Colour::WHITE){
        colourNum = 0; 
    } else {
        colourNum = 1; 
    }
    // blackMoves = 0; 
    // whiteMoves = 0;
}

bool Computer4::move(Board *board, std::pair<int, int> start, std::pair<int, int> finish, char tempChar){ 
    
//0 1 -> end
// 2 3 -> start

    
    //once we have finished opening moves, we can value checkmate over all other moves
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


    // here we want to value checkmate as our primary move 

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

    //check if check is possible
    for(auto a: moves){
        Piece* p = b->getPiece(a[2], a[3]);
        if(b->causesOpposingCheck(p, make_pair(a[0], a[1]))){
            b->move(make_pair(a[2], a[3]), make_pair(a[0], a[1]), '\0');
            return true;
        }
    }

    //for each attacking peice, check if it's occupied - capture

    // if bishop or knight dont have capture moves, continue with other piece
    int numAttackers = 0; 
    vector<vector<int>> attackers; 

    for(auto a: moves){
        if((b->getPiece(a[0], a[1])) != nullptr){
            vector<int> tempAttackers;
            attackers.push_back(vector<int>{a[0], a[1], a[2], a[3]});
            // tempAttackers.push_back(a[0]);
            // tempAttackers.push_back(a[1]);
            // tempAttackers.push_back(a[2]);
            // tempAttackers.push_back(a[3]);
            for(auto b: moves){
                if(b[0] == a[0] && b[1] == a[1] && b[2] != a[2] && b[3] != a[3]){
                    numAttackers++;
                    attackers.push_back(vector<int>{b[0], b[1], b[2], b[3]});
                }
            }

            if(numAttackers > 0){
                break;
            }
        }
    }
    //attacker at pos 0 wil always be intial piece


    if(numAttackers >= 1){
        for(auto a: attackers){
            if(b->getPiece(a[2], a[3])->getType() == Type::PAWN){
                b->move(make_pair(a[2], a[3]), make_pair(a[0], a[1]), '\0');
                return true;
            }
        }
        for(auto a: attackers){
            if(b->getPiece(a[2], a[3])->getType() == Type::BISHOP){
                b->move(make_pair(a[2], a[3]), make_pair(a[0], a[1]), '\0');
                return true;
            }
        }
       for(auto a: attackers){
            if(b->getPiece(a[2], a[3])->getType() == Type::KNIGHT){
                b->move(make_pair(a[2], a[3]), make_pair(a[0], a[1]), '\0');
                return true;
            }
        }
       for(auto a: attackers){
            if(b->getPiece(a[2], a[3])->getType() == Type::ROOK){
                b->move(make_pair(a[2], a[3]), make_pair(a[0], a[1]), '\0');
                return true;
            }
        }
        for(auto a: attackers){
            if(b->getPiece(a[2], a[3])->getType() == Type::QUEEN){
                b->move(make_pair(a[2], a[3]), make_pair(a[0], a[1]), '\0');
                return true;
            }
        }
        for(auto a: attackers){
            if(b->getPiece(a[2], a[3])->getType() == Type::KING){
                b->move(make_pair(a[2], a[3]), make_pair(a[0], a[1]), '\0');
                return true;
            }
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

    return b->move(make_pair(a[2], a[3]), make_pair(a[0], a[1]), '\0');

    return isMoved; 
        

}   