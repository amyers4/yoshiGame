#ifndef KINGBOMB_H
#define KINGBOMB_H

#include <vector>
#include "enemy.h"
#include "bomb.h"

class Bomb;

class KingBomb: public Enemy {
	public:
		static KingBomb* getInstance();
		virtual void update(Uint32 ticks);
		virtual void advanceFrame(Uint32 ticks);
		virtual void draw() const;
		void addToBombList(Bomb* b);
		void addToFreeList(Bomb* b);
		void removeFromBombList(Bomb* b);
	   void clear();
		int getNumBombs() const;
		int getNumFreeBombs() const;
	private:
	
		bool throwing;
		std::vector<Bomb*> bombs;
		std::vector<Bomb*> freeBombs;
		KingBomb(const std::string&);
		KingBomb(const KingBomb&);
};
#endif
