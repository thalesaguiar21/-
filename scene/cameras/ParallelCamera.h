#ifndef _PARALLELCAM_H_
#define _PARALLELCAM_H_

#include "Camera.h"

class ParallelCamera : public Camera {
	private:
		float left;
		float right;
		float top;
		float bottom;
	public:
		ParallelCamera( void );
		ParallelCamera( Point3 from, Point3 at, float left, float right, float top, 
			float bottom );
		Ray shootRay( float s, float t );
};

#include "ParallelCamera.inl"

#endif