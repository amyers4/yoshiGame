#ifndef HEALTH_H
#define HEALTH_H

#include "drawable.h"
#include <vector>
#include <string>
#include "player.h"

class Health {
	public:
		static Health& getInstance() { static Health health("health"); return health;}
		void draw() const;
		void reset();
		void harm(Player& player);
		void safe();		

		const Image* getImage() const {
			return images[currentFrame];
		}
		
		bool dead() const{
			if(currentFrame == numberOfFrames - 1){
				return true;
			}else{
				return false;
			}
		}
		const SDL_Surface* getSurface() const {
			return images[currentFrame]->getSurface();
		}

	protected:
		std::vector<Image*> images;

		Health(const std::string& name);
		unsigned currentFrame;
		unsigned numberOfFrames;
		float timeSinceLastFrame;
		int viewWidth;
		unsigned safeInterval;
	};

#endif


