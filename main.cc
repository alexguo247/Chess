#include "chessgame.h"
#include <iostream>

using namespace std;

int main()
{
    Chessgame* chess = new Chessgame();
    string cmd;

    while (cin >> cmd) {
        if (cmd == "game") {
            string p1;
            string p2;
            cin >> p1;
            cin >> p2;
            chess->game(p1, p2);
        }
        else if (cmd == "resign") {
            chess->resign();
        }
        else if (cmd == "move") {
            string start;
            string end;
            chess->move(start, end);
        } else if (cmd == "setup") {
            chess->setup();
        } else {
            cout << "Not a valid command" << endl;
        }
    }
    
    delete chess;
    return 0;
}