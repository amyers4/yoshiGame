
#include "kingBomb.h"
#include "ground.h"
#include "player.h"


KingBomb* KingBomb::getInstance() {
  static KingBomb instance("King");
  return &instance;
}
KingBomb::KingBomb(const std::string& name):
	Enemy(name),
	throwing(false),
	bombs(),
	freeBombs()
	{
		setY(Ground::getInstance().getGround(getX(), getY()) - height);
	}
KingBomb::KingBomb(const KingBomb& k):
	Enemy(k),
	throwing(k.throwing),
	bombs({}),
	freeBombs({})
	{
	}
void KingBomb::clear(){
		for(auto b: bombs){
			delete b;
		}
		for(auto b: freeBombs){
			delete b;
		}
	}


void KingBomb::advanceFrame(Uint32 ticks){
	timeSinceLastFrame+=ticks;
	if(throwing){
		if(timeSinceLastFrame > frameInterval){
			if(currentFrame == 2){
				currentFrame = 1;
			}else if(currentFrame == 1){
				currentFrame = 0;
			}else{
				currentFrame = 2;
				throwing = false;
				if(freeBombs.empty()){
					Bomb* newBomb = new Bomb("bomb");
					newBomb->setY(getY() + 100);
					newBomb->setX(getX() + 20);
					newBomb->setVelocityX(-90);
					addToBombList(newBomb);
					newBomb->throwBomb();
					Player::getInstance()->attach(newBomb);
				
				}else{
					addToBombList(freeBombs.back());
					freeBombs.back()->setY(getY() + 100);
					freeBombs.back()->setX(getX() + 2);
					freeBombs.back()->setVelocityX(-90);
					freeBombs.back()->throwBomb();
					freeBombs.pop_back();
				}
			}
			timeSinceLastFrame = 0;
		}

	}else{
		currentFrame = 2;
	}
}

void KingBomb::update(Uint32 ticks) {
	advanceFrame(ticks);	
//	Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
//	setPosition(getPosition() + incr);
	static int timeSinceLastThrow = 0;
	static int comp = (rand() % 8) + 1;
	float distsq = (getX() - player.getX()) * (getX() - player.getX());
	if(distsq < 250 * 250){
		if(throwing){
			timeSinceLastThrow = 0;
		}else{
			timeSinceLastThrow += ticks;
		}
		if(timeSinceLastThrow > comp * 500){
			timeSinceLastFrame = 0;
			throwing = true;
			comp = (rand() % 4) + 1;
		}
	}
	for(auto b: bombs){
		b->update(ticks);
	}
		

}
void KingBomb::draw() const{
	images[currentFrame]->draw(getX(), getY(), getScale());
	for(auto b: bombs){
		
		b->draw();
	}
}

void KingBomb::addToBombList(Bomb* b){
	bombs.push_back(b);
}
void KingBomb::addToFreeList(Bomb* b){
	freeBombs.push_back(b);
}
void KingBomb::removeFromBombList(Bomb* b){
	auto it = bombs.begin();
	while(it != bombs.end()){
		if(*it == b){
			it = bombs.erase(it);
		}else{
			it++;
		}
	}
}

int KingBomb::getNumBombs() const{
	return bombs.size();
}
int KingBomb::getNumFreeBombs()const {
	return freeBombs.size();
}
