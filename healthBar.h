#include "SDL.h"
#include "gameData.h"
#include "clock.h"
#include "drawable.h"
#include "ioMod.h"
#include <SDL_ttf.h>

class HealthBar : public Drawable {
public:
  HealthBar(const std::string&);
  void draw() const;
  void update(Uint32);
  void reset() { currentLength = barRect.w; }
	
  bool isDead(){return currentLength < .04;}

  HealthBar(const HealthBar&) = delete;
  HealthBar& operator=(const HealthBar&) = delete;

  virtual int getScaledWidth() const  { return barRect.w; }
  virtual int getScaledHeight() const { return barRect.h; }
  virtual const Image* getImage() const { 
    throw std::string("No image in HealthBar");
  }
private:
  SDL_Renderer* renderer;
  TTF_Font* font;
  SDL_Rect barRect;
  Clock& clock;
  int currentLength;
  int increment;  
  float interval; // elapsed time for each decrement (1000ms=1sec)
  int deltaTime;
  SDL_Color barColor;
  SDL_Color backColor;
  IoMod& io;
};
