#include "Light.h"

Vector3 Origin;
		float Intensity;

Light::Light(void) {
	origin_ = Vector3(0.f);
	intensity_ = 0.f; 
}

Light::Light(Vector3 origin, float intensity) {
	origin_ = origin;
	intensity_ = intensity;
}

bool Light::IsIlluminating(Point3 point) {
	return true;
}

Ray Light::GetShadowRay(Point3 surface) {
	return Ray(surface, UnitVector(origin() - surface));
}