#include "sdl_wrap.h"
#include <iostream>
using namespace std;

// Just must declare a global variable (or at the start of main)
// Don't do anything with this object. It just handles the start and end of SDL.
SDL_Runner r;

int main() {
  Screen s{640,480};
  colour1 white{'\xff', '\xff', '\xff'};
  colour1 blue{'\x0', '\x0', '\xff'};
  s.add_img("man", "stickman.png");
  s.draw_rect(0, 0, 640, 480, white);
  s.draw_rect(310, 230, 20, 20, blue);
  s.draw_string("Hello there", 20, 50, colour1{'\xff','\x00','\xff'});
  s.draw_img("man", 200, 0);
  s.update();
  // Just waiting to read an int so the program doesn't end immediately.
  // in the future we will see better ways to do this!
  int x;
  cin >> x;
}
