#include "Metalic.h"

Metalic::Metalic( Vector3 albedo, float refCoef_ ) {
  set_ref_coef(refCoef_);
  set_diffuse(albedo);
  set_prop(Vector3(0.01, 1.0, 0.0));
}

bool Metalic::Scatter( Ray incident, const HitRecord rec, Vector3 &attenuation, Ray &scattered ) {
	auto reflected = Reflect(UnitVector(incident.Direction()), rec.normal);
	scattered = Ray(rec.hit, reflected + ref_coef() * RandomInUnitSphere());
	attenuation = diffuse();	
	return (dot(scattered.Direction(), rec.normal) > 0);
}
