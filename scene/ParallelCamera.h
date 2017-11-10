#ifndef _PARALLELCAM_H_
#define _PARALLELCAM_H_

#include "Camera.h"

class ParallelCamera : public Camera {
	private:
		float left;
		float right;
		float top;
		float bottom;
		Vector3 randomInUnitDisk();
	public:
		ParallelCamera( void );
		ParallelCamera( Point3 from, Point3 at, Vector3 vup, float fov, 
			float aspect, float aperture, float focus, float left, float right, 
			float top, float bottom );
		Ray shootRay( float s, float t );
};

#include "ParallelCamera.inl"

#endif