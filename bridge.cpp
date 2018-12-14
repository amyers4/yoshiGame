#include "player.h"

Player::Player(const std::string& name) :
	MultiSprite(name),
	baseVelocity(getVelocity()),
	running(false),
	walking(false){
	
	}

Player::Player(const Player& p) :
	MultiSprite(p),
	baseVelocity(p.getVelocity()),
	running(p.running),
	walking(p.walking)
	{

	}

Player& Player::operator=(const Player& p){
	MultiSprite::operator=(p);
	baseVelocity=p.baseVelocity;
	running=p.running;
	walking=p.walking;
	return *this;
}

void Player::advanceFrame(Uint32 ticks){
	timeSinceLastFrame += ticks;
	if((running && (timeSinceLastFrame > .5 * frameInterval)) || 
		(walking && (timeSinceLastFrame > frameInterval))){
		if(getVelocityX() > 0){
			currentFrame = (currentFrame+1)%(numberOfFrames/2);
		}else{
			currentFrame = (currentFrame+1)%(numberOfFrames/2)
									+ (numberOfFrames/2);
		}
		
		timeSinceLastFrame = 0;

	}
}
	


void Player::stop(){
	setVelocityX(.93*getVelocityX());
	setVelocityY(0);
	walking = false;
	running = false;
}

void Player::right(){
	setVelocityX(running?baseVelocity[0]*2:baseVelocity[0]);
}

void Player::left(){
	setVelocityX(running?-baseVelocity[0]*2:-baseVelocity[0]);
}

void Player::update(Uint32 ticks) {
	advanceFrame(ticks);	
	Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
	setPosition(getPosition() + incr);
}

void Player::run(){
	running=true;
	walking=false;
}
void Player::walk(){
	running=false;
	walking = true;
}


