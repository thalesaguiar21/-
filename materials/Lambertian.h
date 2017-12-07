#ifndef _LAMBERTIAN_MAT_H_
#define _LAMBERTIAN_MAT_H_

#include "Material.h"

class Lambertian : public Material {
public:
	Lambertian ( Vector3 albedo, float absorption );
	bool Scatter( Ray incident, const HitRecord rec, Vector3 &attenuation, Ray &scattered ) override;
};

#include "Lambertian.inl"

#endif
