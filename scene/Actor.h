#ifndef _ACTOR_H_
#define _ACTOR_H_

#include <iostream>
#include "../utils/Vec3.h"

class Actor {
public:
	// Object's starting point
	Point3 origin;
	
	/* This method checks if the given Ray hits the caller
		 
		 @param Ray The ray that is being shooted
		 @return True if the given Ray hits the caller, False otherwise */
	virtual bool hit (const Ray & r_) = 0;

	/* This method returns the normal vector surface at the point
		 where the given Ray hits the caller.

		 @param Ray The Ray shooted at the image.
		 @return Vec3 The normal vector surface.*/
	virtual Vec3 getNormal(const Ray & r_, bool lowerRoot=false) = 0;
};
#endif
