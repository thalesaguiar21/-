#ifndef _SQUARE_H_
#define _SQUARE_H_

#include "../scene/Actor.h"
#include "../utils/Vec3.h"
#include "../utils/Ray.h"

class Square : public Actor 
{
public:
	// A vector representing the square's diagonal
  Ray diagonal;

  /* Creates a new square with the upper left corner at origin and
     the given diagonal.*/
  Square (Point3 origin, Ray diagonal) 
  {
    this->origin = origin;
    this->diagonal = diagonal;
  }

  // Not implemented
  inline bool hit(const Ray & r_, bool lowerRoot=false) override 
  {
  	return true;
  }

  inline Vec3 getNormal(const Ray & r_, bool lowerRoot=false) override 
  {
    return Vec3 (0, 0, 0);
  }
};

#endif
