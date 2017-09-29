#ifndef _LAMBERTIAN_MAT_H_
#define _LAMBERTIAN_MAT_H_

#include "Material.h"

namespace materials {
	class Lambertian : public Material {
	public:
		Lambertian ( Vector3 albedo, float absorption );
  	bool Diffusion( Ray incident, Ray &diffused, Point3 hitPoint,
										Vector3 normal ) override;
	protected:
		Vector3 Reflect( Ray incident, Vector3 normal ) override;
	};
}

#include "Lambertian.inl"

#endif
