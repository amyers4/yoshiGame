#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>
#include "sprite.h"
#include "gameData.h"
#include "menuEngine.h"
#include "renderContext.h"

MenuEngine::~MenuEngine() { 
	delete event;
	}

MenuEngine::MenuEngine() :
  event(new SDL_Event()),
  clock( Clock::getInstance() ),
  renderer( RenderContext::getInstance()->getRenderer() ),
  menu( renderer ),
  optionChoice(-1),
  goombasOption(false),
  numGoombas(0)
{
}

void MenuEngine::draw() const {
  menu.draw();
  SDL_RenderPresent(renderer);
}

bool MenuEngine::goombasOptionChosen() { 
  if ( goombasOption ) {
    goombasOption = false;
    return true; 
  }
  return false;
}

void MenuEngine::update(Uint32) {
}

void MenuEngine::play() {
//  SDL_Event event;
  const Uint8* keystate;
  bool done = false;

  while ( !done ) {
    // The next loop polls for events, guarding against key bounce:
    while ( SDL_PollEvent(event) ) {
      keystate = SDL_GetKeyboardState(NULL);
      if (event->type ==  SDL_QUIT) { done = true; break; }
      if(event->type == SDL_KEYDOWN) {
        if (keystate[SDL_SCANCODE_ESCAPE] || keystate[SDL_SCANCODE_Q]) {
          done = true;
          break;
        }
        if (keystate[SDL_SCANCODE_DOWN] ) menu.incrIcon();
        if (keystate[SDL_SCANCODE_UP] ) menu.decrIcon();
        if (keystate[SDL_SCANCODE_RETURN] ) {
          menu.lightOn();
          optionChoice = menu.getOptionNo();
          if ( optionChoice == 1  || optionChoice == 2) done = true;
          if ( optionChoice == 0 ) {
            goombasOption = true;
            numGoombas = menu.getNumGoombas();
            //std::cout << "No is: " << numStars << std::endl;
          }
        }
      }
      if(event->type == SDL_KEYUP) {
        menu.lightOff();
      }
    }
    // In this section of the event loop we allow key bounce:
    draw();
    //update(ticks);
  }
}
