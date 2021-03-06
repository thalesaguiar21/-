#ifndef _RAY_H_
#define _RAY_H_

#include "Vector3.h"

namespace utils {
  class Ray {
    public:
      // The origin of the vector
      Point3 origin;
      Vector3 dir;

      Ray( void );
      Ray( Point3 origin, Point3 dir);
      Vector3 Direction( void );
      Point3 PointAt( float );
  };
} // namespace utils

#include "Ray.inl"

#endif
