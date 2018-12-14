#include "player.h"
#include "imageFactory.h"


Player::Player(const std::string& name) :
	MultiSprite(name),
	baseVelocity(getVelocity()),
	observers(),
	running(false),
	walking(false),
	up(false),
	down(false),
	jumping(false),
	still(false),
	actionStart(false),
	bImages(ImageFactory::getInstance()->getImages(name+"/bImages")),
	rightJumpFrames(ImageFactory::getInstance()->getImages(name+"/rightJump")),
	bRightJumpFrames(ImageFactory::getInstance()->getImages(name+"/bRightJump")),
	leftJumpFrames(ImageFactory::getInstance()->getImages(name+"/leftJump")),
	bLeftJumpFrames(ImageFactory::getInstance()->getImages(name+"/bLeftJump")),
	stillFrames(ImageFactory::getInstance()->getImages(name+"/still")),
	bStillFrames(ImageFactory::getInstance()->getImages(name+"/bStill")),
	rightTongueFrames(ImageFactory::getInstance()->
									getImages(name+"/rightTongue")),
	leftTongueFrames(ImageFactory::getInstance()->
									getImages(name+"/leftTongue")),
	height(Gamedata::getInstance().getXmlInt(name+"/height")),
	mass(Gamedata::getInstance().getXmlInt(name+"/mass"))
	{
		setY(Ground::getInstance().getGround(getX(), getY())-height);
	}

Player::Player(const Player& p) :
	MultiSprite(p),
	baseVelocity(p.getVelocity()),
	observers(p.observers),
	running(p.running),
	walking(p.walking),
	up(p.up),
	down(p.down),
	jumping(p.jumping),
	still(p.still),
	actionStart(p.actionStart),
	bImages(p.bImages),
	rightJumpFrames(p.rightJumpFrames),
	bRightJumpFrames(p.bRightJumpFrames),
	leftJumpFrames(p.leftJumpFrames),
	bLeftJumpFrames(p.bLeftJumpFrames),
	stillFrames(p.stillFrames),
	bStillFrames(p.bStillFrames),
	rightTongueFrames(p.rightTongueFrames),
	leftTongueFrames(p.leftTongueFrames),
	height(p.height),
	mass(p.mass)
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
	bool right;
	if(getVelocityX() > 0){
		right = true;
	}else{
		right = false;
	}
	
	if(jumping){
		still = false;
		if(up){
			if(right){
				currentFrame=1;
			}else{
				currentFrame=4;
			}
		}else{
			if(right){
				currentFrame=2;
			}else{
				currentFrame=3;
			}
		}
	
	}else if(abs(getVelocityX()) < 50 && abs(getVelocityY()) < 50){
		still = true;
		if(right){
			currentFrame=0;
		}else{
			currentFrame=1;
		}
	}
	else if((running && (timeSinceLastFrame > .5 * frameInterval)) || 
		(walking && (timeSinceLastFrame > frameInterval))){
		still = false;
		if(getVelocityX() > 0){
			currentFrame = (currentFrame+1)%(numberOfFrames/2);
		}else{
			currentFrame = (currentFrame+1)%(numberOfFrames/2)
									+ (numberOfFrames/2);
		}
		
		timeSinceLastFrame = 0;

		
	}
}
	

void Player::attach(Enemy* newObserver){
	observers.push_back(newObserver);
}

void Player::detach(Enemy* obs){
	auto it = observers.begin();
	while(it != observers.end()){
		if(*it == obs){
			it = observers.erase(it);
		}else{
			it++;
		}
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
	static float timeInJump = 0;
	static float lastJumpHeight = -1;
	static float startingY = -1;

	if(explosion){
		explosion->update(ticks);
		if(explosion -> chunkCount() == 0){
			delete explosion;
			explosion = NULL;
		}
		return;
	}

	advanceFrame(ticks);	
		float incr = getVelocityX() * static_cast<float>(ticks) * 0.001;
		setX(getX() + incr);
	setY(Ground::getInstance().getGround(getX(), getY() + height) - height);
	if(jumping){
		if(startingY < 0){
			startingY = Ground::getInstance().getGround(getX(), getY());
		}
		timeInJump += static_cast<float>(ticks) * .001;
		float difference = .5 * 80 * timeInJump * timeInJump;
		float vDist = (75 * timeInJump) - difference;
		if(!down && vDist < lastJumpHeight){
			up = false;
			down = true;
		}
		lastJumpHeight = vDist;		
		setY(startingY - (2.75*vDist) - height);
		float groundY=(Ground::getInstance().getGround(getX(), getY() + height));
		if((getY() + height) > groundY){
			setY(groundY - height);
			jumping = false;
			up = false;
			down = false;
			startingY = -1;
			timeInJump = 0;
		}
	}
	
	
	for(auto o: observers){
		o->notify(getPosition());
	}

}

void Player::draw() const {
	if(explosion){explosion->draw(); return;}
	if(still && (currentFrame == 0 || currentFrame == 1)){
		stillFrames[currentFrame]->draw(getX(), getY(), getScale());		
	//if sticking tongue out
	}else if(jumping){
		if(getVelocityX() > 0){
			//safeguarding against laggy frame update
			if(currentFrame == 1 || currentFrame == 2){
					rightJumpFrames[currentFrame]->draw(getX(), getY(), getScale());
			} else {
					images[currentFrame]->draw(getX(), getY(), getScale());
			}	
		}else{			
			if(currentFrame == 3 || currentFrame == 4){
					leftJumpFrames[currentFrame]->draw(getX(), getY(), getScale());
			} else {
					images[currentFrame]->draw(getX(), getY(), getScale());
			}	
		}	
	}else{
			images[currentFrame]->draw(getX(), getY(), getScale());
	}

}
void Player::run(){
	running=true;
	walking=false;
}
void Player::walk(){
	running=false;
	walking = true;
}


void Player::jump(){
	if(!jumping){
		jumping = true;
		up = true;
		down = false;
	}
	running = false;
	walking = false;
}
