#ifndef GOOMBA_H
#define GOOMBA_H

#include "enemy.h"
#include "ground.h"
#include "gameData.h"

class Goomba : public Enemy {
	public:
		virtual ~Goomba();
		Goomba(const std::string&);
		Goomba(const Goomba&);
  		Goomba& operator=(const Goomba&) = delete;
		virtual void draw() const;
  		virtual void update(Uint32 ticks);
		void squash();
		bool isDead(){return dead || done;}
	private:
		MultiSprite* dead;
		int height;
		bool done;
		
};
#endif
