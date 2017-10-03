#include "Metalic.h"


namespace materials {

  Metalic::Metalic( Vector3 albedo, float refCoef_ ) {
    refCoef = refCoef_;
    properties = albedo;
  }

  bool Metalic::Diffusion( Ray incident, Ray &diffused, Point3 hitPoint,
                          Vector3 normal ) {
    auto unitIncident = Ray(Vector3(0,0,0), UnitVector(incident.Direction()));
    Vector3 unitNormal = UnitVector(normal);
    auto reflected = Reflect(unitIncident, unitNormal);
    auto scatered = Ray(hitPoint, reflected);
    return dot(scatered.Direction(), normal) > 0;
  }

  Vector3 Metalic::Reflect( Ray incident, Vector3 normal ) {
    return 2 * dot(incident.Direction(), normal) * normal;
  }
}
