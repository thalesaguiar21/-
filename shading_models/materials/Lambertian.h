#ifndef _LAMBERTIAN_MAT_H_
#define _LAMBERTIAN_MAT_H_

#include "Material.h"

class Lambertian : public Material {
	public:
		Lambertian( void );
		Lambertian( Vector3 albedo, float absorption, int reflections );
		bool Scatter( Ray incident, const HitRecord rec, Vector3 &attenuation, Ray &scattered ) override;
		
	protected:
		Vector3 Reflect( Vector3 incident, Vector3 normal ) override;
};

#include "Lambertian.inl"

#endif
