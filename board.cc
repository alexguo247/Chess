#include "piece.h"
#include "board.h"
#include "rook.h"
#include "bishop.h"
#include "king.h"
#include "queen.h"
#include "knight.h"
#include "pawn.h"

#include <set>
#include <iostream>

using namespace std;

Board::Board()
{
    vector<Piece *> row;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            row.push_back(nullptr);
        }
        grid.push_back(row);
        row = {};
    }
}

Piece *Board::getPiece(int row, int col)
{
    return grid[row][col];
}

void Board::move(pair<int, int> start, pair<int, int> end, char promotion) {
    Piece *p = getPiece(start.first, start.second);

    if (!p->checkMove(end, *this)) {
        cout << "Invalid move!";
        return;
    }

    Type t = p->getType();
    Colour c = p->getColour();

    if (t == Type::KING && end.second - start.second == 2) {
        // castle right side
        setOrCreatePiece(p, end.first, end.second, false, t, c);
        setOrCreatePiece(getPiece(start.first, 7), start.first, 5, false, t, c);
        deletePiece(start.first, 7);
        deletePiece(start.first, start.second);
    } else if (p->getType() == Type::KING && start.second - end.second == 2) {
        // castle left side
        setOrCreatePiece(p, end.first, end.second, false, t, c);
        setOrCreatePiece(getPiece(start.first, 0), start.first, 3, false, t, c);
        deletePiece(start.first, 0);
        deletePiece(start.first, start.second);
    } else if (p->getType() == Type::PAWN && (end.first == 0 || end.first == 7)) {
        // promotion
        if (promotion == 'k' || promotion == 'K') {
            cout << "Invalid promotion type!" << endl;
        } else {
            setOrCreatePiece(nullptr, end.first, end.second, true, getTypeChar(promotion), c);
            deletePiece(start.first, start.second);
        }
    } else {
        setOrCreatePiece(p, end.first, end.first, false, t, c);
        deletePiece(start.first, start.second);
    }
}

void Board::clearBoard()
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (grid[i][j] != nullptr)
            {
                delete grid[i][j];
                grid[i][j] = nullptr;
            }
        }
    }
}

void Board::deletePiece(int row, int col)
{
    delete grid[row][col];
    grid[row][col] = nullptr;
}

void Board::setOrCreatePiece(Piece *piece, int row, int col, bool isCreate, Type createType, Colour createColour)
{
    if (grid[row][col] != nullptr)
    {
        delete grid[row][col];
        grid[row][col] = nullptr;
    }

    Type t;
    Colour c;

    if (isCreate) {
        t = createType;
        c = createColour;
    } else {
        t = piece->getType();
        c = piece->getColour();
    }

    switch (t)
    {
    case Type::KING:
        grid[row][col] = new King(c, row, col, true);
        break;
    case Type::BISHOP:
        grid[row][col] = new Bishop(c, row, col, true);
        break;
    case Type::ROOK:
        grid[row][col] = new Rook(c, row, col, true);
        break;
    case Type::KNIGHT:
        grid[row][col] = new Knight(c, row, col, true);
        break;
    case Type::QUEEN:
        grid[row][col] = new Queen(c, row, col, true);
        break;
    case Type::PAWN:
        if (piece == nullptr) {
            grid[row][col] = new Pawn(c, row, col, false, false);
        } else {
            bool doubleMove = static_cast<Pawn *>(piece)->hasDoubleMoved();
            grid[row][col] = new Pawn(c, row, col, true, doubleMove);
        }
        break;
    }
}

Type Board::getTypeChar(char p) {
    if (p == 'p' || 'P') {
        return Type::PAWN;
    } else if (p == 'k' || p == 'K') {
        return Type::KING;
    } else if (p == 'q' || p == 'Q') {
        return Type::QUEEN;
    } else if (p == 'r' || p == 'R') {
        return Type::ROOK;
    } else if (p == 'n' || p == 'N') {
        return Type::KNIGHT;
    } else {
        return Type::BISHOP;
    }
}

char Board::getCharType(Piece *p)
{
    if (p == nullptr)
    {
        return ' ';
    }

    // white is upper case
    char type = ' ';
    Colour c = p->getColour();
    Type t = p->getType();

    if (c == Colour::BLACK)
    {
        switch (t)
        {
        case Type::PAWN:
            type = 'p';
            break;
        case Type::KNIGHT:
            type = 'n';
            break;
        case Type::ROOK:
            type = 'r';
            break;
        case Type::BISHOP:
            type = 'b';
            break;
        case Type::QUEEN:
            type = 'q';
            break;
        case Type::KING:
            type = 'k';
            break;
        default:
            break;
        }
    }
    else if (c == Colour::WHITE)
    {
        switch (t)
        {
        case Type::PAWN:
            type = 'P';
            break;
        case Type::KNIGHT:
            type = 'N';
            break;
        case Type::ROOK:
            type = 'R';
            break;
        case Type::BISHOP:
            type = 'B';
            break;
        case Type::QUEEN:
            type = 'Q';
            break;
        case Type::KING:
            type = 'K';
            break;
        default:
            break;
        }
    }

    return type;
}

void Board::print()
{
    cout << endl;

    int rowNum = 8;
    for (int row = 0; row < 8; row++)
    {
        cout << rowNum << " ";
        rowNum--;
        for (int col = 0; col < 8; col++)
        {
            if (grid[row][col] == nullptr)
            {
                if ((row % 2 == 0 && col % 2 == 0) || (row % 2 != 0 && col % 2 != 0))
                {
                    cout << "_";
                }
                else
                {
                    cout << " ";
                }
            }
            else
            {
                cout << getCharType(grid[row][col]);
            }
        }
        cout << endl;
    }

    cout << endl;
    cout << "  abcdefgh" << endl;
}

void Board::setup()
{
    // clean up old board
    clearBoard();

    for (int i = 0; i < 8; i++)
    {
        if (i == 0 || i == 7)
        {
            grid[0][i] = new Rook(Colour::BLACK, 0, i, false);
        }
        else if (i == 1 || i == 6)
        {
            grid[0][i] = new Knight(Colour::BLACK, 0, i, false);
        }
        else if (i == 2 || i == 5)
        {
            grid[0][i] = new Bishop(Colour::BLACK, 0, i, false);
        }
        else if (i == 3)
        {
            grid[0][i] = new Queen(Colour::BLACK, 0, i, false);
        }
        else
        {
            grid[0][i] = new King(Colour::BLACK, 0, i, false);
        }
    }

    for (int i = 0; i < 8; i++)
    {
        grid[1][i] = new Pawn(Colour::BLACK, 1, i, false, false);
        grid[6][i] = new Pawn(Colour::WHITE, 6, i, false, false);
    }

    for (int i = 0; i < 8; i++)
    {
        if (i == 0 || i == 7)
        {
            grid[7][i] = new Rook(Colour::WHITE, 7, i, false);
        }
        else if (i == 1 || i == 6)
        {
            grid[7][i] = new Knight(Colour::WHITE, 7, i, false);
        }
        else if (i == 2 || i == 5)
        {
            grid[7][i] = new Bishop(Colour::WHITE, 7, i, false);
        }
        else if (i == 3)
        {
            grid[7][i] = new Queen(Colour::WHITE, 7, i, false);
        }
        else
        {
            grid[7][i] = new King(Colour::WHITE, 7, i, false);
        }
    }
}
