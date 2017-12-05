#ifndef _METALIC_MAT_H_
#define _METALIC_MAT_H_

#include "Material.h"

using namespace utils;

class Metalic : public Material {
	public:
	  Metalic ( void );
	  Metalic ( Vector3 albedo, float refCoef, int reflections );
	  bool Scatter( Ray incident, const HitRecord rec, Vector3 &attenuation, Ray &scattered ) override;

	protected:
		Vector3 Reflect( Vector3 incident, Vector3 normal ) override;
};

#include "Metalic.inl"

#endif
