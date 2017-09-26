#ifndef _SPHERE_H_
#define _SPHERE_H_

#include "../../utility/Vector3.h"
#include "../../utility/Ray.h"
#include "../../materials/Material.h"
#include "../Hitable.h"
#include <cmath>

using materials::Material;
using hitables::Hitable;
using hitables::HitRecord;
using utils::Vector3;
using utils::Ray;

namespace basicShapes {
  class Sphere : public Hitable {
    public:
      float radius;

      Sphere( void );
      Sphere( Point3 center_, float radius_, Material *material_ );
      bool Hit( Ray r_, HitRecord &rec, float minHit, float maxHit ) override;
  };
} // namespace basicShapes

#include "Sphere.inl"

#endif
