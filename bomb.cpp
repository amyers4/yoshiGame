
#include "bomb.h"
#include "gameData.h"
#include "ground.h"
#include "player.h"

Bomb::Bomb(const std::string& name):
	Enemy(name), justThrown(false), inAir(false),
	mass(Gamedata::getInstance().getXmlInt(name +"/mass")),
	yoshi(Player::getInstance()),
	timeTrackingPlayer(0.0),
	timeInAir(0.0),
	initialHeight(0.0),
	initialX(0.0),
	initialXSpeed(0.0),
	initialYSpeed(0.0)
	{
	}
Bomb::Bomb(const Bomb& b):
	Enemy(b), justThrown(b.justThrown), inAir(b.inAir),
	mass(b.mass),
	yoshi(Player::getInstance()),
	timeTrackingPlayer(0.0),
	timeInAir(0.0),
	initialHeight(0.0),
	initialX(0.0),
	initialXSpeed(0.0),
	initialYSpeed(0.0)
	
	{
	}
void Bomb::throwBomb(){
	justThrown = true;
	inAir = true;
}

void Bomb::update(Uint32 ticks) {
	advanceFrame(ticks);
	if(explosion){
		explosion->update(ticks);
		if(
			PerPixelCollisionStrategy::getInstance().
			execute(*explosion,*yoshi)){
			Health::getInstance().harm();
		}
		if(explosion -> chunkCount() == 0){
			delete explosion;
			explosion = NULL;
			setY(initialHeight);
			timeTrackingPlayer = 0.0;
			setX(initialX);
			setVelocityX(initialXSpeed);
			setVelocityY(initialYSpeed);
			KingBomb::getInstance()->removeFromBombList(this); 
			KingBomb::getInstance()->addToFreeList(this); 
		}
		return;
	}
	if(inAir){
	if(justThrown){
		justThrown = false;
		initialHeight = getY();
		timeInAir = 0.0;
		initialX = getX();
		initialXSpeed = getVelocityX();
		initialYSpeed = getVelocityY();
	}

	setX(initialX + (getVelocityX() * timeInAir));
	int ground = Ground::getInstance().getGround(getX(), getY());
	timeInAir+=(static_cast<float>(ticks) * .001);
	if(getY() + height < ground){
		setY(initialHeight + (9.81 * mass * .5 * timeInAir * timeInAir));
	}else{
		inAir = false;
	}
	}else{
		float incr = getVelocityX() * static_cast<float>(ticks) * .001;
		setX(getX() + incr);
		float distsq = (getX() - player.getX()) * (getX() - player.getX());
		if(distsq < 300*300 || timeTrackingPlayer > 0){
			if(timeTrackingPlayer == 0){
				setVelocityX(1.5 * getVelocityX());
			}
			timeTrackingPlayer+= (static_cast<float>(ticks) * .001);
			if(getX() < player.getX()-15 || (getX() > player.getX() &&
												getX() - player.getX() < 15)){
				setVelocityX(std::abs(getVelocityX()));
			}else{
				setVelocityX(-std::abs(getVelocityX()));
			}
			std::cout<< "t " << timeTrackingPlayer << std::endl;
			if(timeTrackingPlayer >=4){
				explode();
			}
		}
	}
}

bool Bomb::playerUpdate(Uint32 ticks){
	if(explosion){
		explosion->update(ticks);
		if(explosion->chunkCount() > 20){
			//TODO king explosion check
		}
		if(explosion -> chunkCount() == 0){
			delete explosion;
			explosion = NULL;
			KingBomb::getInstance()->addToFreeList(this);
			return false;
		}
	}else{
		//TODO have it increment X and Y based on velocity
		//Update position
		//If hit ground, then explode

	 }
	return true;
}

	
