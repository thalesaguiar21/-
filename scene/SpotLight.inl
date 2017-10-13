#include "SpotLight.h"

SpotLight::SpotLight( void ) {
  // nothing
}

SpotLight::SpotLight( Point3 origin_, Vector3 dir, float intensity, float radius, float fov_ ) {
  Origin = origin_;
  Direction = dir;
  Intensity = intensity;
  Radius = radius;
  theta = fov_ * 3.1415 / 180.0; // spot apperture
}


bool SpotLight::IsIlluminating( Point3 point ) {
  float beta = acos(dot(UnitVector(Direction), UnitVector(point - Origin)));
  return beta < theta;
}

Ray SpotLight::GetShadowRay( Point3 surface ) {
  return Ray(surface, Origin);
}
