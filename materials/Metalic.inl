#include "Metalic.h"

Metalic::Metalic( Texture *albedo_, float refCoef_ ) {
  ref_coef_ = refCoef_;
  albedo = albedo_;
}

bool Metalic::Scatter( Ray incident, const HitRecord rec, Vector3 &attenuation, Ray &scattered ) {
	auto reflected = Reflect(UnitVector(incident.Direction()), rec.normal);
	scattered = Ray(rec.hit, reflected + ref_coef() * RandomInUnitSphere());
	attenuation = albedo->Value(0,0,rec.hit);	
	return (dot(scattered.Direction(), rec.normal) > 0);
}
