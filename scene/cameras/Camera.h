#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "../../utility/Vector3.h"
#include "../../utility/Ray.h"
#include "../../utility/Angles.h"

using namespace utils;

using utils::Vector3;

class Camera {
protected:
	Point3 from;
	Point3 at;
	Vector3 u;
	Vector3 v;
	Vector3 w;

	Vector3 randomInUnitDisk() {	
	  Vector3 p;
	  do {
	    p = 2.0 * Vector3(drand48(), drand48(), 0) - Vector3(1,1,0);
	  } while(dot(p,p) >= 1.0);
	  return p;
	}

public:
	Camera( void ) {
		// empty
	}

	Camera( Point3 from, Point3 at ) {

		Vector3 vup (0,1,0);
	  this->from = from;
	  w = UnitVector(from - at);
	  u = UnitVector(Cross(vup, w));
	  v = Cross(w, u);
	}

	virtual Ray shootRay(float s, float t) {
		return Ray();
	}
};

// #include "Camera.inl"

#endif