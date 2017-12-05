#include "Ray.h"

namespace utils {

  Ray::Ray( void ) {
    origin = Point3(0, 0, 0);
    dir = Point3(0, 0, 0);
  }

  Ray::Ray(Point3 origin_, Vector3 dir) {
    origin = origin_;
    this->dir = dir;
  }

  Vector3 Ray::Direction() {
    return dir;
  }

  Point3 Ray::PointAt(float t) {
    return origin + t*Direction();
  }

} // namespace utils
