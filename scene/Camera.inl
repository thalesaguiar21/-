#include "Camera.h"

#include "../utility/Vector3.h"
#include "../utility/Ray.h"

using namespace utils;

Camera::Camera( void ) {
  origin = Point3(0, 0 ,0);
  llc = Point3(0, 0, 0);
  horizontal = Vector3(0, 0, 0);
  vertical = Vector3(0, 0, 0);
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
