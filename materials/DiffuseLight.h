#ifndef _DIFFUSE_LIGHT_H_
#define _DIFFUSE_LIGHT_H_

#include "Material.h"

class DiffuseLight : public Material {
	public:
		DiffuseLight() {}
		bool Scatter( Ray incident, const HitRecord rec, Vector3 &attenuation, Ray &scattered ) override;
		virtual Vector3 Emitted(float u, float v, const Vector3 &p) const {
			return emit->Value(u, v, p);
		}

	private:
		Texture *emit;
};


#endif