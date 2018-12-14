#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>
#include "viewport.h"
#include "ioMod.h"
//#include "clock.h"
#include "kingBomb.h"
#include <stdbool.h>

class Hud {
public:
  static Hud& getInstance();
  ~Hud();
  void draw(int fps, int);
  void toggle();
  SDL_Renderer* getRenderer() const { return renderer; }

private:
  int init;
  int x;
  int y;
  int w;
  int h;
  bool display;
  Viewport& viewport;
//  Clock& clock;
  SDL_Renderer* renderer;
  TTF_Font* font;
  SDL_Color textColor;
  const IoMod& ioMod;
  Hud();
  Hud(const Hud&) = delete;
  Hud& operator=(const Hud&) = delete;


};
