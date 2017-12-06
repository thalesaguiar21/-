#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include "../../utility/Vector3.h"
#include "../../utility/Ray.h"
#include "../../hitables/HitRecord.h"
#include "../models/ShadingType.h"

using utils::Vector3;
using utils::Ray;

class Material {
	public:
		bool virtual Scatter( Ray incident, const HitRecord rec, Vector3 &attenuation, Ray &scattered ) = 0;

		float ref_coef() const { return ref_coef_; }
		void set_ref_coef(float ref_coef) { 
			if(ref_coef > MAX_REFLECTION_COEFFICIENT)
				ref_coef_ = MAX_REFLECTION_COEFFICIENT;
			else	
				ref_coef_ = ref_coef; 
		}

		RGB diffuse() const { return diffuse_; }
		void set_diffuse(RGB value) { diffuse_ = value; }
		RGB specular() const { return specular_; }
		void set_specular(RGB value) { specular_ = value; }
		Vector3 prop() const { return prop_; }
		void set_prop(Vector3 value) { prop_ = value; }
    float shader_value() const { return shader_value_; }
    void set_shader_value(float value) { 
    	if(value > MAX_SHADER_VALUE)
    		shader_value_ = MAX_SHADER_VALUE;
    	else
    		shader_value_ = value; 
    }

    ShadingType shading_type() const { return shader; }

	protected:
		ShadingType shader;
		const int MAX_SHADER_VALUE = 50;
		const int MAX_REFLECTION_COEFFICIENT = 1.0f;
 		Vector3 virtual Reflect( Vector3 incident, Vector3 normal ) = 0;
 		Vector3 RandomInUnitSphere() {
			Vector3 p;
			do {
				p = 2.0 * (Vector3(drand48(), drand48(), drand48()) - Vector3(1.0));
			} while (dot(p, p) >= 1.0);
			return p;
		}

 	private:
		float ref_coef_;
		float shader_value_;
		Vector3 prop_;
		RGB diffuse_;
		RGB specular_;
};

#endif
