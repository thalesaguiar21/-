#ifndef _HITREC_H_
#define _HITREC_H_

#include "../utility/Vector3.h"
#include "../materials/Material.h"

using utils::Vector3;

class Material;

/*  This structure is created to sotre the information of the instersection
    between a Ray and a Hitable object inside the world.
*/
struct HitRecord {
  float root;
  float u;
  float v;
  Point3 hit;
  Vector3 normal;
  Material *mat;
};

#endif
