#include <cmath>
#include "ground.h"
#include "gameData.h"

Ground& Ground::getInstance() {
  static Ground ground; 
  return ground;
}
Ground::Ground()
{
}

float Ground::getGround(float currX, float currY) const{
	if(currX < 560){
		return 980;
	}else if(currX < 1250){
		if(currY <= (979 - ((currX - 560) * .32699))){
			return (972 - ((currX - 560) * .32699));
		}else{
			return 980;
		}
	}else{
		return 750;
	}
}








