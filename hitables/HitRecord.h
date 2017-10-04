#ifndef _HITREC_H_
#define _HITREC_H_

#include "../utility/Vector3.h"
#include "../materials/Material.h"

using utils::Vector3;

/*  This structure is created to sotre the information of the instersection
    between a Ray and a Hitable object inside the world.
*/
struct HitRecord {
  float root;
  Point3 hitPoint;
  Vector3 normal;
  Material *material;
};

#endif
