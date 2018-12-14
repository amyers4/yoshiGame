#ifndef CS_H
#define CS_H



#include <cmath>
#include "drawable.h"

class CollisionStrategy {
public:
  virtual bool execute(const Drawable&, const Drawable&) const = 0;
  virtual ~CollisionStrategy() {}
};

class RectangularCollisionStrategy : public CollisionStrategy {
public:
  RectangularCollisionStrategy() {}
  virtual bool execute(const Drawable&, const Drawable&) const;
};

class MidPointCollisionStrategy : public CollisionStrategy {
public:
  MidPointCollisionStrategy() {}
  virtual bool execute(const Drawable&, const Drawable&) const;
  float distance(float, float, float, float) const;
};

class PerPixelCollisionStrategy : public CollisionStrategy {
public:
  static PerPixelCollisionStrategy& getInstance(){
	  static PerPixelCollisionStrategy instance;
	  return instance;
	}
  virtual bool execute(const Drawable&, const Drawable&) const;
private:
  bool isVisible(Uint32, SDL_Surface*) const;
  PerPixelCollisionStrategy() {}
};
#endif
