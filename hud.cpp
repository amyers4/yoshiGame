#include <SDL_image.h>
#include <sstream>
#include "hud.h"
#include "gameData.h"
#include "renderContext.h"

Hud& Hud::getInstance() {
  static Hud instance;
  return instance;
}

Hud::~Hud() {
  TTF_CloseFont(font);
  TTF_Quit();
}

Hud::Hud() :
  init(TTF_Init()),
  x(Gamedata::getInstance().getXmlInt("hud/x")),
  y(Gamedata::getInstance().getXmlInt("hud/y")),
  w(Gamedata::getInstance().getXmlInt("hud/w")),
  h(Gamedata::getInstance().getXmlInt("hud/h")),
  display(true),
 viewport(Viewport::getInstance()),
  renderer( RenderContext::getInstance()->getRenderer() ),
  font(TTF_OpenFont(Gamedata::getInstance().getXmlStr("font/file").c_str(),
                    Gamedata::getInstance().getXmlInt("hud/font/size"))),
  textColor({0, 140, 140, 0}),
 ioMod( IoMod::getInstance() )
{
  if ( init == -1 ) {
    throw std::string("error: Couldn't init font");
  }
  if (font == NULL) {
    throw std::string("error: font not found");
  }
  textColor.r = Gamedata::getInstance().getXmlInt("hud/r");
  textColor.g = Gamedata::getInstance().getXmlInt("hud/g");
  textColor.b = Gamedata::getInstance().getXmlInt("hud/b");
  textColor.a = Gamedata::getInstance().getXmlInt("hud/a");
}



void Hud::toggle(){
	display = !display;
}

void Hud::draw(int fps, int gLeft) {
	 
	 if(!display){
		 return;
	}
	
    int fontSize = Gamedata::getInstance().getXmlInt("hud/font/size");
	 int distx = x+5;
    int disty = y+5;

    std::stringstream strm;
    strm << "FPS: " << fps;
    ioMod.writeText(strm.str(), distx, disty, textColor, font);
    disty = disty + fontSize + 3;

	 std::stringstream strm2;
    strm2 << "F1: toggle HUD";
    ioMod.writeText(strm2.str(), distx, disty, textColor, font);
    disty = disty + fontSize + 3;
	 
	 std::stringstream strm0;
    strm0 << "R: restart game";
    ioMod.writeText(strm0.str(), distx, disty, textColor, font);
    disty = disty + fontSize + 3;

    std::stringstream strm3;
    strm3 << "<-: Move Yoshi left";
    ioMod.writeText(strm3.str(), distx, disty, textColor, font);
    disty = disty + fontSize + 3;
    
	 std::stringstream strm4;
    strm4 << "->: Move Yoshi right";
    ioMod.writeText(strm4.str(), distx, disty, textColor, font);
    disty = disty + fontSize + 3;
	 
	 std::stringstream strm6;
    strm6 << "Up: Jump";
    ioMod.writeText(strm6.str(), distx, disty, textColor, font);
    disty = disty + fontSize + 3;
    
	 std::stringstream strm5;
    strm5 << "Hold shift to run";
    ioMod.writeText(strm5.str(), distx, disty, textColor, font);
    disty = disty + fontSize + 3;
	 
	 std::stringstream strm52;
    strm52 << "Jump on the Goombas!";
    ioMod.writeText(strm52.str(), distx, disty, textColor, font);
    disty = disty + fontSize + 8;
	 
	 std::stringstream strm12;
    strm12 << "Remaining Goombas: " << gLeft;
    ioMod.writeText(strm12.str(), distx, disty, textColor, font);
    disty = disty + fontSize + 8;
	 
	 std::stringstream strm600;
    strm600 << "(Toggle God Mode with G)";
    ioMod.writeText(strm600.str(), distx, disty, textColor, font);
    disty = disty + fontSize + 8;
	 
    SDL_Rect r;
    r.x = x;
    r.y = y;
    r.w = w;
    r.h = h;

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255/5 );

    SDL_RenderFillRect( renderer, &r );

    SDL_SetRenderDrawColor( renderer, 0, 255, 255, 255 );
    SDL_RenderDrawRect( renderer, &r );
}
