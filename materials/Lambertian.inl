#include "Lambertian.h"


Lambertian::Lambertian( Texture *albedo_, float absortion ) {
	ref_coef_ = absortion;
	albedo = albedo_;
}

bool Lambertian::Scatter( Ray incident, const HitRecord rec, Vector3 &attenuation, Ray &scattered ) {
	Vector3 target = rec.hit + rec.normal + RandomInUnitSphere();
	scattered = Ray(rec.hit, target - rec.hit);
	attenuation = albedo->Value(0,0,rec.hit);
	return true;
}
