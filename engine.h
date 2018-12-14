#include <vector>
#include <SDL.h>
#include "ioMod.h"
#include "hud.h"
#include "renderContext.h"
#include "clock.h"
#include "world.h"
#include "viewport.h"
#include "gameData.h"
#include "collisionStrategy.h"
#include "health.h"
#include "ground.h"
#include "goomba.h"
#include "menuEngine.h"

class Player;
class Engine {
public:
  Engine ();
  ~Engine ();
  Engine(const Engine&) = delete;
  Engine& operator=(const Engine&) = delete;
  bool play();
  void switchSprite();
private:
//  MenuEngine menuEngine;
  
  const RenderContext* rc;
  const IoMod& io;
  Clock& clock;


  Health health;

  SDL_Renderer * const renderer;
  SDL_Color textColor;
  World clouds, hills, ground;
  Hud& hud;
  PerPixelCollisionStrategy perPixel;
  Viewport& viewport;
  Player player;
  std::vector<Goomba*> goombas;
  
  int currentSprite;

  int initialGoombas;
  int deadGoombas;

  bool godMode;
  bool makeVideo;

  void draw() const;
  void update(Uint32);

  void printScales() const;
  void checkForCollisions();
};
