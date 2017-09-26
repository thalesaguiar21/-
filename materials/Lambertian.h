#ifndef _LAMBERTIAN_MAT_H_
#define _LAMBERTIAN_MAT_H_

#include "Material.h"

namespace materials {
	class Lambertian : public Material {
	public:
		Lambertian ( Vector3 albedo, float absorption );
  	bool diffusion( Ray r_, Ray &diffused, Point3 hitPoint,
										Vector3 normal ) override;
	};
}

#include "Lambertian.inl"

#endif
