#include "Lambertian.h"


Lambertian::Lambertian( Vector3 albedo, float absortion ) {
	set_diffuse(albedo);
	set_prop(Vector3(0.01, 1.0, 0.0));
	set_ref_coef(absortion);
}

bool Lambertian::Scatter( Ray incident, const HitRecord rec, Vector3 &attenuation, Ray &scattered ) {
	Vector3 target = rec.hit + rec.normal + RandomInUnitSphere();
	scattered = Ray(rec.hit, target - rec.hit);
	attenuation = diffuse();
	return true;
}
