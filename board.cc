#include "piece.h"
#include "board.h"
#include "rook.h"
#include "bishop.h"
#include "king.h"
#include "queen.h"
#include "knight.h"
#include "pawn.h"
#include <cmath>
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

bool Board::move(pair<int, int> start, pair<int, int> end, char promotion)
{
    Piece *p = getPiece(start.first, start.second);

    if (!p->checkMove(end, *this))
    {
        cout << "Invalid move! Move again." << endl;
        return false;
    }

    Type t = p->getType();
    Colour c = p->getColour();

    if (t == Type::KING && end.second - start.second == 2)
    {
        // castle right side
        setOrCreatePiece(p, end.first, end.second, false, t, c);
        setOrCreatePiece(getPiece(start.first, 7), start.first, 5, false, t, c);
        deletePiece(start.first, 7);
        deletePiece(start.first, start.second);
    }
    else if (p->getType() == Type::KING && start.second - end.second == 2)
    {
        // castle left side
        setOrCreatePiece(p, end.first, end.second, false, t, c);
        setOrCreatePiece(getPiece(start.first, 0), start.first, 3, false, t, c);
        deletePiece(start.first, 0);
        deletePiece(start.first, start.second);
    }
    else if (p->getType() == Type::PAWN && (end.first == 0 || end.first == 7))
    {
        // promotion
        if (promotion == '\0' || promotion == 'k' || promotion == 'K')
        {
            cout << "Invalid promotion type! Move again." << endl;
            return false;
        }
        else
        {
            setOrCreatePiece(nullptr, end.first, end.second, true, getTypeChar(promotion), c);
            deletePiece(start.first, start.second);
        }
    }
    else
    {
        // basic move
        setOrCreatePiece(p, end.first, end.second, false, t, c);
        deletePiece(start.first, start.second);
    }
    return true;
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

    if (isCreate)
    {
        t = createType;
        c = createColour;
    }
    else
    {
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
        if (piece == nullptr)
        {
            grid[row][col] = new Pawn(c, row, col, false, false);
        }
        else
        {
            bool doubleMove = static_cast<Pawn *>(piece)->hasDoubleMoved();
            grid[row][col] = new Pawn(c, row, col, true, doubleMove);
        }
        break;
    }
}

Type Board::getTypeChar(char p)
{
    if (p == 'p' || p == 'P')
    {
        return Type::PAWN;
    }
    else if (p == 'k' || p == 'K')
    {
        return Type::KING;
    }
    else if (p == 'q' || p == 'Q')
    {
        return Type::QUEEN;
    }
    else if (p == 'r' || p == 'R')
    {
        return Type::ROOK;
    }
    else if (p == 'n' || p == 'N')
    {
        return Type::KNIGHT;
    }
    else
    {
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
                    cout << " ";
                }
                else
                {
                    cout << "_";
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

pair<int, int> Board::findKing(Colour c)
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (getPiece(i, j) != nullptr && getPiece(i, j)->getType() == Type::KING && getPiece(i, j)->getColour() == c)
            {
                return pair<int, int>{i, j};
            }
        }
    }
    return pair<int, int>{-1, -1};
}

bool Board::validateBoard()
{
    bool valid = true;
    int whiteKingCount = 0;
    int blackKingCount = 0;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (i == 0 || i == 7)
            {
                if (getPiece(i, j)->getType() == Type::PAWN)
                {
                    valid = false;
                }
            }
            if (getPiece(i, j)->getType() == Type::KING)
            {
                if (getPiece(i, j)->getColour() == Colour::BLACK)
                {
                    if (inDanger(Colour::BLACK, i, j))
                    {
                        valid = false;
                    }
                    blackKingCount++;
                }
                else
                {
                    if (inDanger(Colour::WHITE, i, j))
                    {
                        valid = false;
                    }
                    whiteKingCount++;
                }
            }
        }
    }
    if (whiteKingCount != 1 || blackKingCount != 1)
    {
        valid = false;
    }

    return valid;
}

void Board::updateAttackingMoves()
{
    whiteAttackingMoves.clear();
    blackAttackingMoves.clear();
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (getPiece(i, j) == nullptr)
            {
                continue;
            }

            Colour c = getPiece(i, j)->getColour();
            vector<vector<int>> attackMoves = getPiece(i, j)->getAttackMoves(*this);

            for (auto a : attackMoves)
            {
                if (c == Colour::WHITE)
                {
                    whiteAttackingMoves.push_back(a);
                }
                else
                {
                    blackAttackingMoves.push_back(a);
                }
            }
        }
    }
}

vector<vector<int>> Board::getAttackers(Colour c)
{
    vector<vector<int>> attackers;
    pair<int, int> kingCoords = findKing(c);
    int kingRow = kingCoords.first;
    int kingCol = kingCoords.second;
    if (c == Colour::BLACK)
    {
        for (auto move : whiteAttackingMoves)
        {
            if (move[0] == kingRow && move[1] == kingCol)
            {
                attackers.push_back(move);
            }
        }
    }
    else
    {
        for (auto move : blackAttackingMoves)
        {
            if (move[0] == kingRow && move[1] == kingCol)
            {
                attackers.push_back(move);
            }
        }
    }
    return attackers;
}

bool Board::inDanger(Colour c, int row, int col)
{
    if (c == Colour::BLACK)
    {
        for (auto move : whiteAttackingMoves)
        {
            if (move[0] == row && move[1] == col)
            {
                return true;
            }
        }
    }
    else
    {
        for (auto move : blackAttackingMoves)
        {
            if (move[0] == row && move[1] == col)
            {
                return true;
            }
        }
    }
    return false;
}

bool Board::canBlock(Colour c, int row, int col)
{
    if (c == Colour::BLACK)
    {
        for (auto move : blackAttackingMoves)
        {
            if (move[0] == row && move[1] == col)
            {
                return true;
            }
        }
    }
    else
    {
        for (auto move : whiteAttackingMoves)
        {
            if (move[0] == row && move[1] == col)
            {
                return true;
            }
        }
    }
    return false;
}

bool Board::inCheck(Colour turn)
{
    Colour attacked = (turn == Colour::WHITE) ? Colour::BLACK : Colour::WHITE;
    pair<int, int> kingCoords = findKing(attacked);
    int kingRow = kingCoords.first;
    int kingCol = kingCoords.second;
    if (inDanger(attacked, kingRow, kingCol) && !inCheckmate(turn))
    {
        return true;
    }
    return false;
}

bool Board::inCheckmate(Colour turn)
{
    Colour attacked = (turn == Colour::WHITE) ? Colour::BLACK : Colour::WHITE;
    vector<vector<int>> attackers = getAttackers(attacked);
    vector<pair<int, int>> dirs{
        pair<int, int>{-1, -1},
        pair<int, int>{-1, 0},
        pair<int, int>{-1, 1},
        pair<int, int>{0, -1},
        pair<int, int>{0, 1},
        pair<int, int>{1, -1},
        pair<int, int>{1, 0},
        pair<int, int>{1, 1},
    };
    pair<int, int> kingCoords = findKing(attacked);
    int kingRow = kingCoords.first;
    int kingCol = kingCoords.second;
    Piece *currKing = getPiece(kingRow, kingCol);
    bool isCheckmate = true;
    // No attackers
    if (attackers.size() == 0)
    {
        isCheckmate = false;
    }
    // 1 attacker
    else if (attackers.size() == 1)
    {
        int attackerRow = attackers[0][2];
        int attackerCol = attackers[0][3];
        int rowDiff = attackerRow - kingRow;
        int colDiff = attackerCol - kingCol;

        // Same row (rook / queen)
        if (rowDiff == 0)
        {
            // Escape by moving away
            for (auto &d : dirs)
            {
                int nr = kingRow + d.first;
                int nc = kingRow + d.second;
                if (currKing->checkMove({nr, nc}, *this) && !inDanger(attacked, kingRow + d.first, kingCol + d.second))
                {
                    isCheckmate = false;
                }
            }
            // Escape by blocking
            if (colDiff > 0)
            {
                for (int i = attackerCol; i > kingCol; i--)
                {
                    if (canBlock(attacked, attackerRow, i))
                    {
                        isCheckmate = false;
                    }
                }
            }
            else
            {
                for (int i = attackerCol; i < kingCol; i++)
                {
                    if (canBlock(attacked, attackerRow, i))
                    {
                        isCheckmate = false;
                    }
                }
            }
        }
        // Same column (rook / queen)
        else if (colDiff == 0)
        {
            // Escape by moving away
            for (auto &d : dirs)
            {
                int nr = kingRow + d.first;
                int nc = kingRow + d.second;
                if (currKing->checkMove({nr, nc}, *this) && !inDanger(attacked, kingRow + d.first, kingCol + d.second))
                {
                    isCheckmate = false;
                }
            }
            // Escape by blocking
            if (rowDiff > 0)
            {
                for (int i = attackerRow; i > kingRow; i--)
                {
                    if (canBlock(attacked, i, attackerCol))
                    {
                        isCheckmate = false;
                    }
                }
            }
            else
            {
                for (int i = attackerRow; i < kingRow; i++)
                {
                    if (canBlock(attacked, i, attackerCol))
                    {
                        isCheckmate = false;
                    }
                }
            }
        }
        // Same diagonal (bishop / queen / pawn)
        else if (abs((double)(colDiff) / (rowDiff)) == 1.0)
        {
            // Escape by moving away
            for (auto &d : dirs)
            {
                int nr = kingRow + d.first;
                int nc = kingRow + d.second;
                if (currKing->checkMove({nr, nc}, *this) && !inDanger(attacked, kingRow + d.first, kingCol + d.second))
                {
                    isCheckmate = false;
                }
            }
            // Escape by blocking
            // Down right
            if (rowDiff > 0 && colDiff > 0)
            {
                int i = 1;
                while (kingRow + i <= attackerRow)
                {
                    if (canBlock(attacked, kingRow + i, kingCol + i))
                    {
                        isCheckmate = false;
                    }
                    i++;
                }
            }
            // Up right
            else if (rowDiff < 0 && colDiff > 0)
            {
                int i = 1;
                while (kingRow - i >= attackerRow)
                {
                    if (canBlock(attacked, kingRow - i, kingCol + i))
                    {
                        isCheckmate = false;
                    }
                    i++;
                }
            }
            // Down left
            else if (rowDiff > 0 && colDiff < 0)
            {
                int i = 1;
                while (kingRow + i <= attackerRow)
                {
                    if (canBlock(attacked, kingRow + i, kingCol - i))
                    {
                        isCheckmate = false;
                    }
                    i++;
                }
            }
            // Up left
            else
            {
                int i = 1;
                while (kingRow - i >= attackerRow)
                {
                    if (canBlock(attacked, kingRow - i, kingCol - i))
                    {
                        isCheckmate = false;
                    }
                    i++;
                }
            }
        }
        // Horse
        else
        {
            for (auto &d : dirs)
            {
                int nr = kingRow + d.first;
                int nc = kingRow + d.second;
                if (currKing->checkMove({nr, nc}, *this) && !inDanger(attacked, kingRow + d.first, kingCol + d.second))
                {
                    isCheckmate = false;
                }
            }
        }
    }
    // 2 attackers
    else
    {
        for (auto &d : dirs)
        {
            int nr = kingRow + d.first;
            int nc = kingRow + d.second;
            if (currKing->checkMove({nr, nc}, *this) && !inDanger(attacked, kingRow + d.first, kingCol + d.second))
            {
                isCheckmate = false;
            }
        }
    }
    return isCheckmate;
}

bool Board::inStalemate(Colour turn)
{
    if (turn == Colour::WHITE && blackAttackingMoves.size() == 0)
    {
        return true;
    }
    else if (turn == Colour::BLACK && whiteAttackingMoves.size() == 0)
    {
        return true;
    }
    return false;
}

bool Board::causesCheck(Piece *p, pair<int, int> n)
{
    Colour colour = p->getColour();
    Type type = p->getType();
    pair<int, int> kingPos = findKing(colour);
    if (inDanger(colour, kingPos.first, kingPos.second))
    {
        return true;
    }

    int currRow = p->getPos().first;
    int currCol = p->getPos().second;
    if (getPiece(n.first, n.second) != nullptr)
    {
        Type takingType = getPiece(n.first, n.second)->getType();
        Colour takingColour = getPiece(n.first, n.second)->getColour();
        if (takingColour == colour)
        {
            return true;
        }
        // Takes the piece
        setOrCreatePiece(p, n.first, n.second, false, type, colour);
        // Delete original piece
        deletePiece(currRow, currCol);
        p = nullptr;
        updateAttackingMoves();
        bool ret = inDanger(colour, kingPos.first, kingPos.second);
        setOrCreatePiece(nullptr, currRow, currCol, true, type, colour);
        setOrCreatePiece(nullptr, n.first, n.second, true, takingType, takingColour);
        return ret;
    }
    else
    {
        setOrCreatePiece(p, n.first, n.second, false, type, colour);
        deletePiece(currRow, currCol);
        p = nullptr;
        updateAttackingMoves();
        bool ret = inDanger(colour, kingPos.first, kingPos.second);
        setOrCreatePiece(nullptr, currRow, currCol, true, type, colour);
        return ret;
    }
    return false;
}