#ifndef _BLINNPHONG_MAT_H_
#define _BLINNPHONG_MAT_H_

#include <algorithm>

#include "Material.h"

class BlinnPhong : public Material {
public:
	RGB diffuse;
	RGB spec;
	float kd; // Diffuse coefficient
	float ks; // Specular coefficient

	BlinnPhong( void );
	BlinnPhong( RGB diffuse_, RGB specular_, float kd_, float ks_ );
  bool Diffusion( Ray incident, Ray &diffused, Point3 hitPoint,
                  Vector3 normal ) override;
protected:
  Vector3 Reflect( Vector3 incident, Vector3 normal ) override;
};

#include "BlinnPhong.inl"

#endif
