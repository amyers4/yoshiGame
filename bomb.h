#ifndef	BOMB_H
#define BOMB_H
#include "gameData.h"
#include "enemy.h"
#include "kingBomb.h"
#include "player.h"
#include "health.h"
#include "collisionStrategy.h"

class Player;

class Bomb : public Enemy {
	public:
		Bomb& operator=(const Bomb&) = delete;
		Bomb(const std::string&);
		Bomb(const Bomb&);
		virtual void update(Uint32 ticks);
		bool playerUpdate(Uint32 ticks);
		void throwBomb();
	private:
		bool justThrown;
		bool inAir;
		int mass;
		Player* yoshi;
		float timeTrackingPlayer;
		float timeInAir;
		float initialHeight;
		float initialX;
		float initialXSpeed;
		float initialYSpeed;
};
#endif
