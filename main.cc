#include "chessgame.h"
#include <iostream>
#include <sstream>

using namespace std;

int main()
{
    Chessgame* chess = new Chessgame();
    string line;
    string cmd;

    while (getline(cin, line)) {
        stringstream input(line);
        input >> cmd;
        if (cmd == "game") {
            string p1;
            string p2;
            input >> p1;
            input >> p2;
            chess->game(p1, p2);
        }
        else if (cmd == "resign") {
            chess->resign();
        }
        else if (cmd == "move") {
            string start;
            string end;
            char promotion = '\0';
            input >> start;
            input >> end;
            input >> promotion;
            chess->move(start, end, promotion);
        } else if (cmd == "setup") {
            chess->setup();
        } else {
            cout << "Not a valid command" << endl;
        }
    }
    
    delete chess;
    return 0;
}