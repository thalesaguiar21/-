#include "ParallelCamera.h"

ParallelCamera::ParallelCamera( void ) {
	ParallelCamera(	Point3(0,0,2), Point3(0,0,0),-2, 2, -2, 2 );
}

ParallelCamera::ParallelCamera( Point3 from, Point3 at, float left, float right, 
  float top, float bottom ) : Camera(from, at) {

  this->left = left;
  this->right = right;
  this->top = top;
  this->bottom = bottom;
}

Ray ParallelCamera::shootRay( float s, float t) {
	float u_ = left + (right-left)*s;
  float v_ = bottom + (top-bottom)*(1-t);
  Vector3 tmpOrigin = from + u_*u + v_*v;
  Ray ray = Ray(tmpOrigin, Point3(0,0,0));
  ray.setDir(-w);
  return ray;
}
