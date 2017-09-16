#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "../utility/Vector3.h"
#include "../utility/Ray.h"

using namespace utils;

class Camera {
  public:
    Point3 origin;
    Point3 llc;
    Vector3 horizontal;
    Vector3 vertical;

    Camera( void );
    Camera ( Point3 origin, Point3 llc, Vector3 horizontal, Vector3 vertical );
    Ray ShootRay( float u, float v );
};

#include "Camera.inl"

#endif
