#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include "../utility/Vector3.h"
#include "../utility/Ray.h"

using utils::Vector3;
using utils::Ray;

class Material {
	public:
		bool virtual Diffusion( Ray incident, Ray &diffused, Point3 hitPoint,
													  Vector3 normal ) = 0;

		float ref_coef() const { return ref_coef_; };
		void set_ref_coef(float value) { ref_coef_ = value; };
		RGB diffuse() const { return diffuse_; };
		void set_diffuse(RGB value) { diffuse_ = value; };
		RGB specular() const { return specular_; };
		void set_specular(RGB value) { specular_ = value; };
		Vector3 prop() const { return prop_; };
		void set_prop(Vector3 value) { prop_ = value; };

	protected:
 		Vector3 virtual Reflect( Vector3 incident, Vector3 normal ) = 0;

 	private:
		float ref_coef_;
		Vector3 prop_;
		RGB diffuse_;
		RGB specular_;

};

#endif
