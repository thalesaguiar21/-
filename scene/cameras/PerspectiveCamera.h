#ifndef _PERSPERCTIVE_CAM_
#define _PERSPERCTIVE_CAM_

#include "Camera.h"

class PerspectiveCamera : public Camera {
private:
		Vector3 horizontal;
		Vector3 vertical;
		Vector3 lowerLeftCorner;
		float lensRadius;
public:
	PerspectiveCamera( void );
	PerspectiveCamera( Point3 from, Point3 at, float fov, float aspect, 
		float aperture, float focus );
	Ray shootRay( float s, float t );
};

#include "PerspectiveCamera.inl"

#endif