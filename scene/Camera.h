#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "../utility/Vector3.h"
#include "../utility/Ray.h"

using namespace utils;
/*
  This class yields to create an abstraction of the point from where an observer
  is looking to scene and plane to create a view limit of this observer.
*/
class Camera {
  public:
    // Origin of the camera. Rays will be shooted from this point.
    Point3 origin;
    // Lower left corner of the camera, or start point of the view plane.
    Point3 llc;
    // Horizontal direction of the view plane
    Vector3 horizontal;
    // Vertical direction of the view plane
    Vector3 vertical;

    //  Create a camera with all points and directions initialized at (0,0,0).
    Camera( void );
    Camera ( Point3 origin, Point3 llc, Vector3 horizontal, Vector3 vertical );

    /*  Create a ray by lerping the the horizontal and vertical axis of the
        view plane with the given u and v scalars.

        @param float The horizontal scalar
        @param float The vertical scalar
    */
    Ray ShootRay( float u, float v );
};

#include "Camera.inl"

#endif
