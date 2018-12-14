
#include "enemy.h"
#include "sprite.h"

Enemy::Enemy(const std::string& name):
	MultiSprite(name),
	player(0,0)
	{
	}

Enemy::Enemy(const Enemy& e) :
	MultiSprite(e),
	player(e.player)
	{

	}

Enemy& Enemy::operator=(const Enemy& e){
	
  Drawable::operator=(e);
  return *this;
}
void Enemy::notify(const Vector2f& playerPos){
	player = playerPos;
}




