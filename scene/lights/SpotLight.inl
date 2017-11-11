#include "SpotLight.h"

SpotLight::SpotLight( void ) {
  // nothing
}

SpotLight::SpotLight(Point3 origin, Vector3 dir, float intensity, float radius, 
										 float fov) : Light(origin, intensity) {
  direction_ = dir;
  radius_ = radius;
  aperture_angle_ = radians(fov);
}

bool SpotLight::IsIlluminating(Point3 point) {
	Vector3 unit_direction = UnitVector(direction());
	Vector3 back_vec_dir = UnitVector(point - origin());
  float back_ray_angle = acos(dot(unit_direction, back_vec_dir));
  return back_ray_angle < aperture_angle();
}

Ray SpotLight::GetShadowRay( Point3 surface ) {
  return Ray(surface, origin() - surface);
}
