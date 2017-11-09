#include "PerspectiveCamera.h"

PerspectiveCamera::PerspectiveCamera( void ) {
	PerspectiveCamera(Point3(0,0,2), Point3(0,0,0), Vector3(0,1,0), 50, 2, 1, 1);
}


PerspectiveCamera::PerspectiveCamera( Point3 from, Point3 at, Vector3 vup, 
	float fov, float aspect, float aperture, float focus ) {

	lensRadius = aperture / 2.0;
  float theta = fov * PI/180.0;
  float half_height = tan(theta/2);
  float half_width = aspect * half_height;
  this->from = from;
  w = UnitVector(from - at);
  u = UnitVector(Cross(vup, w));
  v = Cross(w, u);
  lowerLeftCorner = from - half_width*focus*u - half_height*focus*v - focus*w;
  horizontal = 2 * half_width * focus * u;
  vertical = 2 * half_height * focus * v;
}

Vector3 PerspectiveCamera::randomInUnitDisk() {	
  Vector3 p;
  do {
    p = 2.0 * Vector3(drand48(), drand48(), 0) - Vector3(1,1,0);
  } while(dot(p,p) >= 1.0);
  return p;
}

Ray PerspectiveCamera::shootRay( float s, float t) {
	Vector3 rd = lensRadius * randomInUnitDisk();
  Vector3 offset = u * rd.X() + v * rd.Y();
  Point3 term = lowerLeftCorner + s*horizontal + t*vertical;
  return Ray(from + offset, term);
}
