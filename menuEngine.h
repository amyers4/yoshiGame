#include <vector>
#include <SDL.h>
#include "menu.h"

class MenuEngine {
public:
  MenuEngine ();
  ~MenuEngine ();
  void play();
  int getOptionChoice() const { return optionChoice; }
  bool goombasOptionChosen();
  int getNumGoombas() const { return numGoombas; }

private:
  SDL_Event* event;
  Clock& clock;
  SDL_Renderer * const renderer;
  Menu menu;
  int optionChoice;
  bool goombasOption;
  int numGoombas;

  void draw() const;
  void update(Uint32);

  MenuEngine(const MenuEngine&);
  MenuEngine& operator=(const MenuEngine&);
};
