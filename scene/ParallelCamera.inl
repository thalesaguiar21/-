#include "ParallelCamera.h"

ParallelCamera::ParallelCamera( void ) {
	ParallelCamera(	Point3(0,0,2), Point3(0,0,0), Vector3(0,1,0), 50, 2, 1, 1, -2, 2, -2, 2 );
}


ParallelCamera::ParallelCamera( Point3 from, Point3 at, Vector3 vup, float fov, 
	float aspect, float aperture, float focus, float left, float right, float top,
	float bottom ) {

	lensRadius = aperture / 2.0;
  float theta = fov * PI/180.0;
  float half_height = tan(theta/2);
  float half_width = aspect * half_height;
  this->from = from;
  w = UnitVector(from - at);
  u = UnitVector(Cross(vup, w));
  v = Cross(w, u);
  this->left = left;
  this->right = right;
  this->top = top;
  this->bottom = bottom;
  lowerLeftCorner = from - half_width*focus*u - half_height*focus*v - focus*w;
  horizontal = 2 * half_width * focus * u;
  vertical = 2 * half_height * focus * v;
}

Vector3 ParallelCamera::randomInUnitDisk() {	
  Vector3 p;
  do {
    p = 2.0 * Vector3(drand48(), drand48(), 0) - Vector3(1,1,0);
  } while(dot(p,p) >= 1.0);
  return p;
}

Ray ParallelCamera::shootRay( float s, float t) {
	float u_ = left + (right-left)*s;
  float v_ = bottom + (top-bottom)*(1-t);
  Vector3 tmpOrigin = from + u_*u + v_*v;
  Ray ray = Ray(tmpOrigin, Point3(0,0,0));
  ray.setDir(-w);
  return ray;
}
