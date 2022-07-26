#include "chessgame.h"
#include <iostream>
#include <sstream>

using namespace std;

int main()
{
    // Screen s{800,800};
    // cout <<"INSIDE DISPLAY PRINT" << endl;
    // colour1 white{'\xff', '\xff', '\xff'};
    // colour1 blue{'\x0', '\x0', '\xff'};
    // s.draw_rect(0, 0, 640, 480, white);
    // s.draw_rect(310, 230, 20, 20, blue);
    // s.update();
    // cout <<"ENDING" << endl;

    Chessgame *chess = new Chessgame();
    string line;
    string cmd;

    while (getline(cin, line))
    {
        if (!line.length()) {
            cout << "No command entered. Try again." << endl;
            continue; 
        }

        stringstream input(line);
        input >> cmd;
        if (cmd == "game")
        {
            string p1;
            string p2;
            input >> p1;
            input >> p2;
            chess->game(p1, p2);
        }
        else if (cmd == "resign")
        {
            chess->resign();
        }
        else if (cmd == "move")
        {
            string start;
            string end;
            char promotion = '\0';
            input >> start;
            input >> end;
            input >> promotion;
            chess->move(start, end, promotion);

        }
        else if (cmd == "setup")
        {
            chess->setup();
        }
        else
        {
            cout << "Not a valid command" << endl;
        }
    }

    chess->printScoreboard();
    delete chess;
    return 0;
}
