#include <SDL.h>
#include <string>
#include "drawable.h"

#ifndef GROUND_H
#define GROUND_H


class Ground {
public:
  static Ground& getInstance();
  float getGround(const float currX, const float currY) const;
private:
  Ground();
  Ground(const Ground&);
  Ground& operator=(const Ground&);
};

#endif
