#ifndef BRIDGE_H
#define BRIDGE_H

#include "multisprite.h"
#include <stdbool.h>
class Player : public MultiSprite {
	public:
		Player(const std::string&);
		Player(const Player&);
		virtual void update(Uint32 ticks);

	 	Player& operator=(const Player&);
		
		void advanceFrame(Uint32);
		void right();
		void left();
		void stop();
		void run();
		void walk();

	private:
		Vector2f baseVelocity;
		bool running;
		bool walking;
};
#endif
