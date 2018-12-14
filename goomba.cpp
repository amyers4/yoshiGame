
#include "goomba.h"

Goomba::~Goomba(){
	if(dead){
		delete dead;
	}
}

Goomba::Goomba(const std::string& name):
	Enemy(name),
	dead(nullptr),
	height(Gamedata::getInstance().getXmlInt(name+"/height")),
	done(false)
	{
	}
Goomba::Goomba(const Goomba& g):
	Enemy(g),
	dead(g.dead),
	height(g.height),
	done(g.done)
	{
	}

void Goomba::update(Uint32 ticks) {
	if(!done && !dead){
		advanceFrame(ticks);	
		float incr = getVelocityX() * static_cast<float>(ticks) * 0.001;
		setX(getX() + incr);
		setY(Ground::getInstance().getGround(getX(), getY())-height);	
		float distsq = (getX() - player.getX()) * (getX() - player.getX());
		if(distsq < 150*150 && distsq > 30 * 30){
			if(getX() < player.getX()){
				setVelocityX(+std::abs(getVelocityX()));
			}else{
				setVelocityX(-std::abs(getVelocityX()));
			}
		}
	

	  if ( getX() < 65) {
   	 setVelocityX( std::abs( getVelocityX() ) );
 	 }
 	 if ( getX() > 2800) {
   	 setVelocityX( -std::abs( getVelocityX() ) );
 	 } 

	}else if (!done){
		dead->update(ticks);
		if(dead->getCurrFrame() == 2){
			done = true;
		}
	}
}

void Goomba::draw() const{
	if(done){return;}
	if(dead){dead->draw();}
	else{MultiSprite::draw();}
}

void Goomba::squash(){
	if(!done && !dead){
		dead = new MultiSprite("deadGoomba");
		dead->setX(getX());
		dead->setY(getY());
		dead->setVelocityX(getVelocityX());
		dead->setVelocityY(getVelocityY());
	}
}
