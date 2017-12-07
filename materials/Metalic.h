#ifndef _METALIC_MAT_H_
#define _METALIC_MAT_H_

#include "Material.h"
#include "../utility/Vector3.h"
#include "../utility/Ray.h"

using namespace utils;

class Metalic : public Material {
public:
  Metalic ( void );
  Metalic ( Texture *albedo, float refCoef_ = 0.5 );
  bool Scatter( Ray incident, const HitRecord rec, Vector3 &attenuation, Ray &scattered ) override;
};

#include "Metalic.inl"

#endif
