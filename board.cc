#include "piece.h"
#include "board.h"
using namespace std;

Piece *Board::getPiece(int row, int col)
{
    return grid[row][col];
}

void Board::setPiece(Piece *piece, int row, int col)
{
    if (grid[row][col] != nullptr)
    {
        delete grid[row][col];
    }
    grid[row][col] = piece;
}

void Board::printBoard()
{
    cout << grid;
}
