#include "textdisplay.h"

using namespace std;

// create empty board
Textdisplay::Textdisplay()
{
    for (int i = 0; i < 8; i++)
    {
        vector<char> tempLine;

        for (int j = 0; j < 8; j++)
        {
            tempLine.push_back(' ');
        }
        theDis.push_back(tempLine);
    }
}

char Textdisplay::getCharType(Piece *p)
{
    if (p == nullptr) {
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

void Textdisplay::setupFromBoard(Board *b)
{
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            theDis[i][j] = getCharType(b->getPiece(i, j));
        }
    }
}

void Textdisplay::notify(Piece *p, std::pair<int, int> oldLoc)
{
    char temp = getCharType(p);
    cout << temp << endl;
    cout << "HELLLO FROM THE OTHER SIDE" << endl;

    theDis[oldLoc.first][oldLoc.second] = ' ';
    theDis[p->getPos().first][p->getPos().second] = temp;
}

ostream &operator<<(std::ostream &out, const Textdisplay &td)
{
    out << endl;

    int rowNum = 8;
    for (int row = 0; row < 8; row++)
    {
        out << rowNum << " ";
        rowNum--;
        for (int col = 0; col < 8; col++)
        {
            if (td.theDis[row][col] == ' ')
            {
                if ((row % 2 == 0 && col % 2 == 0) || (row % 2 != 0 && col % 2 != 0))
                {
                    out << "_";
                }
                else
                {
                    out << " ";
                }
            }
            else
            {
                out << td.theDis[row][col];
            }
        }
        out << endl;
    }

    out << endl;
    out << "  abcdefgh" << endl;

    return out;
}
