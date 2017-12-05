#include "Lambertian.h"

Lambertian::Lambertian( void ) {
	set_diffuse(RGB(0));
	set_prop(Vector3(0.01, 1.0, 0.0));
	set_ref_coef(0.5);
	set_shader_value(1);
	shader = ShadingType::lambertian;
}

Lambertian::Lambertian( Vector3 albedo, float absortion, int reflections ) {
	set_diffuse(albedo);
	set_prop(Vector3(0.01, 1.0, 0.0));
	set_ref_coef(absortion);
	set_shader_value(reflections);
	shader = ShadingType::lambertian;
}

bool Lambertian::Scatter( Ray incident, const HitRecord rec, Vector3 &attenuation, Ray &scattered ) {
	Vector3 target = rec.hit + rec.normal + Reflect(incident.Direction(), rec.normal);
	attenuation = diffuse();
	scattered = Ray(rec.hit, target - rec.hit);
	return true;
}

// RandomInUnitSphere
Vector3 Lambertian::Reflect( Vector3 incident, Vector3 normal ) {
	Vector3 p;
	do {
		p = 2.0 * (Vector3(drand48(), drand48(), drand48()) - Vector3(1.0));
	} while (dot(p, p) >= 1.0);
	return p;
}
