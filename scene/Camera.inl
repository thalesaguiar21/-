#include "Camera.h"

Camera::Camera( void ) {
  origin = Point3(0, 0 , 0);
  llc = Point3(-2, -1, -1);
  horizontal = Vector3(4, 0, 0);
  vertical = Vector3(0, 2, 0);
}

Camera::Camera( Vector3 lookFrom_, Vector3 lookAt_, Vector3 vup, float fov, float aspect ) {
  Vector3 u, v, w;
  float theta = fov * M_PI/180.0;
  float half_height = tan(theta/2);
  float half_width = aspect * half_height;
  origin = lookFrom_;
  w = UnitVector(lookFrom_ - lookAt_);
  u = UnitVector(Cross(vup, w));
  v = Cross(w, u);
  llc = origin - half_width*u  - half_height*v - w;
  horizontal = 2 * half_width * u;
  vertical = 2 * half_height * v;
}

Camera::Camera( Point3 origin_, Point3 llc_, Vector3 horizontal_,
                Vector3 vertical_ ) {
  origin = origin_;
  llc = llc_;
  horizontal = horizontal_;
  vertical = vertical_;
}

inline Ray Camera::ShootRay(float u, float v) {
  Point3 term = llc + u*horizontal + v*vertical;
  return Ray(origin, term);
}
