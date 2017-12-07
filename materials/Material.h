#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include "../utility/Vector3.h"
#include "../utility/Ray.h"
#include "../hitables/HitRecord.h"

using utils::Vector3;
using utils::Ray;

class Material {
	public:
		bool virtual Scatter( Ray incident, const HitRecord rec, Vector3 &attenuation, Ray &scattered ) = 0;

		float ref_coef() const { return ref_coef_; };
		void set_ref_coef(float value) { ref_coef_ = value; };
		RGB diffuse() const { return diffuse_; };
		void set_diffuse(RGB value) { diffuse_ = value; };
		RGB specular() const { return specular_; };
		void set_specular(RGB value) { specular_ = value; };
		Vector3 prop() const { return prop_; };
		void set_prop(Vector3 value) { prop_ = value; };

	protected:
 		Vector3 Reflect( Vector3 incident, Vector3 normal ) {
			return incident - 2*dot(incident, normal) * normal;
		}

		Point3 RandomInUnitSphere() {
			Vector3 p;
			do {
				p = 2.0 * (Vector3(drand48(), drand48(), drand48()) - Vector3(1.0));
			} while (dot(p, p) >= 1.0);
			return p;
		}

 	private:
		float ref_coef_;
		Vector3 prop_;
		RGB diffuse_;
		RGB specular_;

};

#endif
