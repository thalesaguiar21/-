#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include "../utility/Vector3.h"
#include "../utility/Ray.h"
#include "../hitables/HitRecord.h"
#include "textures/Texture.h"

using utils::Vector3;
using utils::Ray;

class Material {
	public:
		bool virtual Scatter( Ray incident, const HitRecord rec, Vector3 &attenuation, Ray &scattered ) = 0;

		float ref_coef() const { return ref_coef_; };
		void set_ref_coef(float value) { ref_coef_ = value; };

	protected:
 		Vector3 Reflect( Vector3 incident, Vector3 normal ) {
			return incident - 2*dot(incident, normal) * normal;
		}

		bool Refract(Vector3 &v, Vector3 &n, float ni_over_nt, Vector3 &refracted) {
			Vector3 uv = UnitVector(v);
			float dt = dot(uv,n);
			float discriminant = 1.0 - ni_over_nt*ni_over_nt*(1-dt*dt);
			if(discriminant > 0) {
				refracted = ni_over_nt * (v - n*dt) - n*sqrt(discriminant);
				return true;
			} else {
				return false;
			}

		}

		Point3 RandomInUnitSphere() {
			Vector3 p;
			do {
				p = 2.0 * (Vector3(drand48(), drand48(), drand48()) - Vector3(1.0));
			} while (dot(p, p) >= 1.0);
			return p;
		}

		Texture *albedo;
		float ref_coef_;
};

#endif
