#include "piece.h"
#include "board.h"
#include "rook.h"
#include "bishop.h"
#include "king.h"
#include "queen.h"
#include "knight.h"
#include "pawn.h"

#include <set>

using namespace std;

Piece* Board::getPiece(int row, int col) {
    return grid[row][col];
}

void Board::setPiece(Piece* piece, int row, int col) {
    if (grid[row][col] != nullptr) {
        delete grid[row][col];
    }
    grid[row][col] = piece;
}

void Board::setup(set<pair<int, int>> &blackAttackingMoves, set<pair<int, int>> &whiteAttackingMoves, pair<int, int> &blackKing, pair<int, int> &whiteKing) {
    // clean up old board
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (grid[i][j] != nullptr) {
                delete grid[i][j];
                grid[i][j] = nullptr;
            }
        }
    }

    for (int i = 0; i < 8; i++) {
        if (i == 0 || i == 7) {
            grid[0][i] = new Rook(Colour::BLACK, 0, i);
        } else if (i == 1 || i == 6) {
            grid[0][i] = new Knight(Colour::BLACK, 0, i);
        } else if (i == 2 || i == 5) {
            grid[0][i] = new Bishop(Colour::BLACK, 0, i);
        } else if (i == 3) {
            grid[0][i] = new Queen(Colour::BLACK, 0, i);
        } else {
            grid[0][i] = new King(Colour::BLACK, 0, i);
        }
    }

    for (int i = 0; i < 8; i++) {
        grid[1][i] = new Pawn(Colour::BLACK, 1, i);
    }

    for (int i = 0; i < 8; i++) {
        if (i == 0 || i == 7) {
            grid[7][i] = new Rook(Colour::WHITE, 7, i);
        } else if (i == 1 || i == 6) {
            grid[7][i] = new Knight(Colour::WHITE, 7, i);
        } else if (i == 2 || i == 5) {
            grid[7][i] = new Bishop(Colour::WHITE, 7, i);
        } else if (i == 3) {
            grid[7][i] = new Queen(Colour::BLACK, 7, i);
        } else {
            grid[7][i] = new King(Colour::BLACK, 7, i);
        }
    }

    whiteKing = pair<int, int>{7, 4};
    blackKing = pair<int, int>{0, 4};

    for (int i = 0; i < 8; i ++) {
        for (int j = 0; j < 8; j++) {
            if (grid[i][j] == nullptr) {
                continue;
            }

            vector<pair<int, int>> attackingMoves = grid[i][j]->getAttackingSquares();
            if (grid[i][j]->getColour() == Colour::BLACK) {
                for (int k = 0; k < attackingMoves.size(); k++) {
                    blackAttackingMoves.insert(attackingMoves[k]);
                }
            } else {
                for (int k = 0; k < attackingMoves.size(); k++) {
                    whiteAttackingMoves.insert(attackingMoves[k]);
                }
            }
        }
    }

}
