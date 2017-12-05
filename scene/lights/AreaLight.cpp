#include "AreaLight.h"

AreaLight:AreaLight(void) {
	set_origin(Point3(0))
}

AreaLight(Point3 center, Vector3 horizontal, Vector3 vertical) {
	set_origin(center);
	horizontal_ = horizontal;
	vertical_ = vertical;
}

bool AreaLight::IsIlluminating(Point3 point) {
	return true;
}

Ray AreaLight::GetShadowRay(Point3 surface) {
	return Ray(Point3(0), Vector3(0));
}