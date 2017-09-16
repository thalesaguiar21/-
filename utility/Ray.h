#ifndef _RAY_H_
#define _RAY_H_

#include "Vector3.h"

namespace utils {
  class Ray {
    public:
      Point3 origin;
      Point3 terminal;

      Ray( void );
      Ray( Point3 origin, Point3 terminal);
      Vector3 Direction( void );
      Point3 PointAt( float );
  };
} // namespace utils

#include "Ray.inl"

#endif
