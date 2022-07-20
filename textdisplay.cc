#include "textdisplay.h"

using namespace std;

// create empty board
Textdisplay::Textdisplay()
{
    theDis = new char *[8];

    for (int i = 0; i < 8; i++)
    {
        theDis[i] = new char[8];
    }
}

Textdisplay::~Textdisplay()
{
    for (int i = 0; i < 8; i++)
    {
        delete[] theDis[i];
    }
    delete[] theDis;
}

char Textdisplay::getCharType(Piece *p)
{
    // white is upper case
    char type;
    if (p->getColour() == Colour::BLACK)
    {
        switch (p->getType())
        {
        case Type::Pawn:
            type = 'p';
            break;
        case Type::Knight:
            type = 'n';
            break;
        case Type::Rook:
            type = 'r';
            break;
        case Type::Bishop:
            type = 'b';
            break;
        case Type::Queen:
            type = 'q';
            break;
        case Type::King:
            type = 'k';
            break;
        default:
            break;
        }
    }
    else if (p->getColour() == Colour::WHITE)
    {
        switch (p->getType())
        {
        case Type::Pawn:
            type = 'P';
            break;
        case Type::Knight:
            type = 'N';
            break;
        case Type::Rook:
            type = 'R';
            break;
        case Type::Bishop:
            type = 'B';
            break;
        case Type::Queen:
            type = 'Q';
            break;
        case Type::King:
            type = 'K';
            break;
        default:
            break;
        }
    }

    return type;
}

void Textdisplay::notify(Piece *p, std::pair<int, int> oldLoc)
{
    char temp = getCharType(p);

    (theDis[oldLoc.first])[oldLoc.second] = ' ';
    (theDis[p->getPos().first])[p->getPos().second] = temp;
}

ostream &operator<<(std::ostream &out, const Textdisplay &td)
{
    for (int row = 7; row >= 0; row--)
    {
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

    return out;
}
