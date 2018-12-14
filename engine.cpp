#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <random>
#include <iomanip>
#include "sprite.h"
#include "multisprite.h"
#include "player.h"
#include "twowaysprite.h"
#include "gameData.h"
#include "engine.h"
#include "frameGenerator.h"
#include "goomba.h"
#include "kingBomb.h"
#include "collisionStrategy.h"


Engine::~Engine() { 
  for(Goomba* sprite : goombas){
	 delete sprite;
  }
  std::cout << "Terminating program" << std::endl;
}

Engine::Engine() :
  menuEngine(),
  rc( RenderContext::getInstance() ),
  io( IoMod::getInstance() ),
  clock( Clock::getInstance() ),
  health(Health::getInstance()),
  renderer( rc->getRenderer() ),
  textColor({140, 43, 8, 255}),
  clouds("clouds", Gamedata::getInstance().getXmlInt("clouds/factor") ),
  hills("hills", Gamedata::getInstance().getXmlInt("hills/factor") ),
  ground("ground", Gamedata::getInstance().getXmlInt("ground/factor") ),
  hud( Hud::getInstance() ),
  perPixel(PerPixelCollisionStrategy::getInstance()),
  viewport( Viewport::getInstance() ),
  player(Player("Yoshi")),
  goombas(),
  currentSprite(0),
  initialGoombas(Gamedata::getInstance*().getXmlInt("defaultGoombas")),
  deadGoombas(0),
  godMode(false),
  makeVideo(false )
{
	clock.pause();
	menuEngine.play();
	clock.unpause();
	
	if(menuEngine.goombasOptionChosen()){
		initialGoombas = menuEngine.getNumGoombas();
	}
	if(menuEngine.getOptionChoice() == 1){
		godMode = false;
	}else{
//	godMode = true;
//	}
	
	
	
	srand(time(NULL));
  for(int i = 0; i < initialGoombas; i++){
	 Goomba* ng = new Goomba("Goomba");
	 int ran = (rand()%3000) + 200;
	 ng->setX(ran);
	 ng->setVelocityX(ran%2 == 0?ng->getVelocityX():-1 * ng->getVelocityX());
  	 ng->setY(Ground::getInstance().getGround(ng->getX(), 900));
	 goombas.emplace_back(ng);
	}
	for(auto gp: goombas){
		player.attach(gp);
	}
  Viewport::getInstance().setObjectToTrack(&player);
  std::cout << "Loading complete" << std::endl;
}

void Engine::draw() const {
  clouds.draw();
  hills.draw();
  ground.draw();

	if(!godMode){
		health.draw();
	}else{
		io.writeText("GOD MODE",250,15);
	}




	player.draw();

  for(Goomba* sprite : goombas){
	 sprite->draw();
  }

//  static int fpsX = Gamedata::getInstance().getXmlInt("view/loc/x");
//  static int fpsY = Gamedata::getInstance().getXmlInt("view/loc/y") + 20;
	int fps = 0;
  if(clock.getSeconds() > 0){
  	fps = clock.getFrames()/clock.getSeconds();
  }
	hud.draw(fps, initialGoombas - deadGoombas);

	if(deadGoombas >= initialGoombas || health.dead()){
		clock.pause();
		if(health.dead()){
			io.writeText("Oh no! The goombas won :( press R to restart",300,400);
		}else{
			io.writeText("You  won! :D press R to play again",300,400);
		}
	}

  viewport.draw(textColor);
  SDL_RenderPresent(renderer);
}

void Engine::update(Uint32 ticks) {
  for(Goomba* sprite : goombas){
	  sprite->update(ticks);
  }

	player.update(ticks);
  clouds.update();
  hills.update();
  ground.update();
	bool hitPlayer = false;
	for(Goomba* g : goombas){
		if(!g->isDead() && perPixel.execute(player, *g)){
			if(player.goingDown()){
				g -> squash();
				deadGoombas++;
			}else{
				hitPlayer = true;
			}
		}
	}

	if(hitPlayer && !godMode){
		health.harm(player);
	}else{
		health.safe();
	}

  viewport.update(); // always update viewport last
}

bool Engine::play() {
  SDL_Event event;
  const Uint8* keystate;
  bool done = false;
  Uint32 ticks = clock.getElapsedTicks();
  FrameGenerator frameGen;

  while ( !done ) {
    // The next loop polls for events, guarding against key bounce:
    while ( SDL_PollEvent(&event) ) {
      keystate = SDL_GetKeyboardState(NULL);
      if (event.type ==  SDL_QUIT) { done = true; break; }
      if(event.type == SDL_KEYDOWN) {
        if (keystate[SDL_SCANCODE_ESCAPE] || keystate[SDL_SCANCODE_Q]) {
          done = true;
          break;
        }
        if ( keystate[SDL_SCANCODE_P] ) {
          if ( clock.isPaused() ) clock.unpause();
          else clock.pause();
        }
        if ( keystate[SDL_SCANCODE_F1] ) {
          hud.toggle();
        }
		  if ( keystate[SDL_SCANCODE_R]){
				clock.unpause();
				return true;
			}
		  if ( keystate[SDL_SCANCODE_G]){
				godMode = !godMode;
			}
        if (keystate[SDL_SCANCODE_F4] && !makeVideo) {
          std::cout << "Initiating frame capture" << std::endl;
          makeVideo = true;
        }
        else if (keystate[SDL_SCANCODE_F4] && makeVideo) {
          std::cout << "Terminating frame capture" << std::endl;
          makeVideo = false;
        }
      }
    }

    // In this section of the event loop we allow key bounce:

    ticks = clock.getElapsedTicks();
    if ( ticks > 0 ) {
      clock.incrFrame();
      if(keystate[SDL_SCANCODE_RIGHT]){
			player.right();
		}
      if(keystate[SDL_SCANCODE_UP]){
			player.jump();
		}
      if(keystate[SDL_SCANCODE_LEFT]){
			player.left();
		}
      if(keystate[SDL_SCANCODE_RSHIFT] || keystate[SDL_SCANCODE_LSHIFT]){
			player.run();
		}else{
			player.walk();
		}
		if(!keystate[SDL_SCANCODE_RIGHT] && !keystate[SDL_SCANCODE_LEFT]){
			player.stop();
		}
		
		
		draw();
      update(ticks);
      if ( makeVideo ) {
        frameGen.makeFrame();
      }
    }
  }
 	return false;
}
