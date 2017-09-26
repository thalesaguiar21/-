#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include "../utility/Vector3.h"
#include "../utility/Ray.h"

using utils::Vector3;
using utils::Ray;

namespace materials {
  class Material {
  public:
  	float refCoef;
  	Vector3 properties;
  	bool virtual diffusion( Ray r_, Ray &diffused, Point3 hitPoint,
  												  Vector3 normal ) = 0;
  protected:
   	Vector3 RandomInUnitSphere();
  };
} // namespace materials

#include "Material.inl"

#endif
