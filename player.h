#ifndef PLAYER_H
#define PLAYER_H

#include "multisprite.h"
#include <vector>
#include "enemy.h"
#include <stdbool.h>
#include "ground.h"


class Player : public MultiSprite {
	public:
		Player(const std::string&);
		Player(const Player&);
		virtual void update(Uint32 ticks);
		virtual void draw() const;
	 	Player& operator=(const Player&);
		
		void advanceFrame(Uint32);
		void right();
		void jump();
		void left();
		void stop();
		void run();
		void walk();
		void attach(Enemy*);
		void detach(Enemy*);



		bool goingDown(){ return down;}

	private:
		Vector2f baseVelocity;
		std::vector<Enemy*> observers;
		bool running;
		bool walking;
		bool up;
		bool down;
		bool jumping;
		bool still;
		bool actionStart;
		std::vector<Image*> bImages;
		std::vector<Image*> rightJumpFrames;
		std::vector<Image*> bRightJumpFrames;
		std::vector<Image*> leftJumpFrames;
		std::vector<Image*> bLeftJumpFrames;
		std::vector<Image*> stillFrames;
		std::vector<Image*> bStillFrames;
		std::vector<Image*> rightTongueFrames;
		std::vector<Image*> leftTongueFrames;
		int height;
		int mass;
};
#endif
