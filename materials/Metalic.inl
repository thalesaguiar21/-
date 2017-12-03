#include "Metalic.h"

Metalic::Metalic( Vector3 albedo, float refCoef_ ) {
  set_ref_coef(refCoef_);
  set_diffuse(albedo);
  set_prop(Vector3(0.01, 1.0, 0.0));
}

bool Metalic::Diffusion( Ray incident, Ray &diffused, Point3 hitPoint,
                        Vector3 normal ) {
	auto reflected = Reflect(UnitVector(incident.Direction()), normal);
	diffused = Ray(hitPoint, reflected);	
	return (dot(diffused.Direction(), normal) > 0);
}

Vector3 Metalic::Reflect( Vector3 incident, Vector3 normal ) {
  return incident - 2 * dot(incident, normal) * normal;
}
