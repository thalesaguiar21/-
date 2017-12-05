#include "Lambertian.h"


Lambertian::Lambertian( Vector3 albedo, float absortion ) {
	set_diffuse(albedo);
	set_prop(Vector3(0.01, 1.0, 0.0));
	set_ref_coef(absortion);
}

bool Lambertian::Scatter( Ray incident, const HitRecord rec, Vector3 &attenuation, Ray &scattered ) {
	Vector3 target = rec.hit + rec.normal + Reflect(incident.Direction(), rec.normal);
	scattered = Ray(rec.hit, target - rec.hit);
	return true;
}

Vector3 Lambertian::Reflect( Vector3 incident, Vector3 normal ) {
	Vector3 p;
	do {
		p = 2.0 * (Vector3(drand48(), drand48(), drand48()) - Vector3(1.0));
	} while (dot(p, p) >= 1.0);
	return p;
}
