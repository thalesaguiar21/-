#ifndef _PERSPERCTIVE_CAM_
#define _PERSPERCTIVE_CAM_

#include "Camera.h"
#include "../utility/Vector3.h"

class PerspectiveCamera : public Camera {
private:
	Vector3 randomInUnitDisk();
public:
	PerspectiveCamera( void );
	PerspectiveCamera( Point3 from, Point3 at, Vector3 vup, float fov, 
			float aspect, float aperture, float focus );
	Ray shootRay( float s, float t );
};

#include "PerspectiveCamera.inl"

#endif