#ifndef ENEMY_H
#define ENEMY_H

#include "multisprite.h"


class Enemy : public MultiSprite {
	public:
		Enemy(const std::string&);
		Enemy(const Enemy&);
		Enemy& operator=(const Enemy& e);
		void notify(const Vector2f& playerPos);
	protected:
		Vector2f player;
};
#endif
