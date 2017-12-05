#include "Metalic.h"

Metalic::Metalic( Vector3 albedo, float refCoef, int reflections ) {
  set_ref_coef(refCoef);
  set_diffuse(albedo);
  set_prop(Vector3(0.01, 1.0, 0.0));
  set_shader_value(reflections);
  shader = ShadingType::lambertian;
}

bool Metalic::Scatter( Ray incident, const HitRecord rec, Vector3 &attenuation, Ray &scattered ) {
	auto reflected = Reflect(UnitVector(incident.Direction()), rec.normal);
	scattered = Ray(rec.hit, reflected);
	attenuation = diffuse();	
	return (dot(scattered.Direction(), rec.normal) > 0);
}

Vector3 Metalic::Reflect( Vector3 incident, Vector3 normal ) {
  return incident - 2 * dot(incident, normal) * normal;
}
