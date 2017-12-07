#ifndef _DIELECTRIC_H_
#define _DIELECTRIC_H_

#include "Material.h"
#include "textures/ConstantTexture.h"

class Dielectric : public Material {

	public:
		Dielectric(void);
		Dielectric(float ref) {
			ref_idx = ref;
			albedo = new ConstantTexture(RGB(1.0,1.0,1.0));
		}

		float Schlick(float cosine, float ref) {
			float r0 = (1 - ref) / (1 + ref);
			r0 = r0*r0;
			return r0 + (1 - r0)*pow((1-cosine), 5);
		}

		bool Scatter( Ray incident, const HitRecord rec, Vector3 &attenuation, Ray &scattered ) override {
			Vector3 outward_normal;
			Vector3 inDir = incident.Direction();
			Vector3 reflected = Reflect(inDir, rec.normal);
			Vector3 refracted;
			attenuation = RGB(1.0);
			float ni_over_nt;
			float cosine;
			float reflect_prob;

			if(dot(inDir, rec.normal)) {
				outward_normal = -1 * rec.normal;
				ni_over_nt = ref_idx;
				cosine = dot(inDir, rec.normal) / inDir.Length();
				cosine = 1 - ref_idx*ref_idx*(1-cosine*cosine);
			} else {
				outward_normal = rec.normal;
				ni_over_nt = 1.0 / ref_idx;
				cosine = -dot(inDir, rec.normal) / inDir.Length();
			}

			if(Refract(inDir, outward_normal, ni_over_nt, refracted)) {
				reflect_prob = Schlick(cosine, ref_idx);
			} else {
				reflect_prob = 1.0;
			}

			if(drand48() < reflect_prob) {
				scattered = Ray(rec.hit, reflected);
			} else {
				scattered = Ray(rec.hit, refracted);
			}
			return true;
		}

	private:
		float ref_idx;

};


#endif