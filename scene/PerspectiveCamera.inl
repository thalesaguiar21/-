#include "PerspectiveCamera.h"

PerspectiveCamera::PerspectiveCamera( void ) {
	PerspectiveCamera(Point3(0,0,2), Point3(0,0,0), 50, 2, 1, 1);
}


PerspectiveCamera::PerspectiveCamera( Point3 from, Point3 at,	float fov, 
  float aspect, float aperture, float focus ) : Camera(from, at) {

  lensRadius = aperture / 2.0;
  float theta = fov * PI/180.0;
  float half_height = tan(theta/2);
  float half_width = aspect * half_height;
  lowerLeftCorner = from - half_width*focus*u - half_height*focus*v - focus*w;
  horizontal = 2 * half_width * focus * u;
  vertical = 2 * half_height * focus * v;
}

Ray PerspectiveCamera::shootRay( float s, float t) {
	Vector3 rd = lensRadius * randomInUnitDisk();
  Vector3 offset = u * rd.X() + v * rd.Y();
  return Ray(from + offset, lowerLeftCorner + s*horizontal + t*vertical - from - offset);
}
