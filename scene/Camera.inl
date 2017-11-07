#include "Camera.h"

Camera::Camera( void ) {
  origin = Point3(0, 0 , 0);
  llc = Point3(-2, -1, -1);
  horizontal = Vector3(4, 0, 0);
  vertical = Vector3(0, 2, 0);
}

Camera::Camera( Vector3 lookFrom_, Vector3 lookAt_, Vector3 vup, float fov, 
      float aspect ) {
  Vector3 u, v, w;
  lens_radius = 1;
  float theta = fov * 3.14159/180.0;
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

Camera::Camera( Vector3 lookFrom_, Vector3 lookAt_, Vector3 vup, float fov, 
      float aspect, float aperture, float focus_dist) {
  lens_radius = aperture / 2.0;
  float theta = fov * 3.14159/180.0;
  float half_height = tan(theta/2);
  float half_width = aspect * half_height;
  origin = lookFrom_;
  w = UnitVector(lookFrom_ - lookAt_);
  u = UnitVector(Cross(vup, w));
  v = Cross(w, u);
  llc = origin - half_width*focus_dist*u  - half_height*focus_dist*v - focus_dist*w;
  horizontal = 2 * half_width * focus_dist * u;
  vertical = 2 * half_height * focus_dist * v;
}

Camera::Camera( Point3 origin_, Point3 llc_, Vector3 horizontal_,
                Vector3 vertical_ ) {
  origin = origin_;
  llc = llc_;
  horizontal = horizontal_;
  vertical = vertical_;
}


inline Vector3 Camera::randomInUnitDisk() {
  Vector3 p;
  do {
    p = 2.0 * Vector3(drand48(), drand48(), 0) - Vector3(1,1,0);
  } while(dot(p,p) >= 1.0);
  return p;
}

inline Ray Camera::ShootRay(float s, float t) {
  Vector3 rd = lens_radius * randomInUnitDisk();
  Vector3 offset = u * rd.X() + v * rd.Y();
  Point3 term = llc + s*horizontal + t*vertical;
  return Ray(origin + offset, term);
}
