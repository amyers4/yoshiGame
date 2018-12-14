#include "health.h"
#include "gameData.h"
#include "imageFactory.h"
#include "viewport.h"
#include "player.h"

Health::Health(const std::string& name) : 
		images(ImageFactory::getInstance()->getImages(name)),
		currentFrame(0),
		numberOfFrames(Gamedata::getInstance().getXmlInt(name+"/frames")),
		timeSinceLastFrame(0),
		viewWidth(Gamedata::getInstance().getXmlInt("view/width")),
		safeInterval(0)
		{
			
			}


void Health::draw() const{
	images[currentFrame]->draw(Viewport::getInstance().getX()+(viewWidth/2)-50, 
										Viewport::getInstance().getY(), 2);	
}

void Health::reset(){
	currentFrame = 0;
	safeInterval=0;
}
		
void Health::harm(Player& player){
	
	if((currentFrame < (numberOfFrames - 1)) && safeInterval > 100){
		currentFrame++;
		safeInterval = 0;
		player.explode();
	}else{
		safeInterval++;
	}
}

void Health::safe(){
	safeInterval++;
}
