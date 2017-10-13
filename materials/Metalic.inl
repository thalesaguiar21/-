#include "Metalic.h"

Metalic::Metalic( Vector3 albedo, float refCoef_ ) {
  refCoef = refCoef_;
  prop = albedo;
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
