#include "BlinnPhong.h"


BlinnPhong::BlinnPhong( void ) {
	//
}

BlinnPhong::BlinnPhong( RGB diffuse_, RGB specular_, Vector3 properties_ ) {
	set_diffuse(diffuse_);
	set_specular(specular_);
	set_prop(properties_);
}

bool BlinnPhong::Diffusion( Ray incident, Ray &diffused, Point3 hitPoint, Vector3 normal ) {
	return true;
}

Vector3 BlinnPhong::Reflect( Vector3 incident, Vector3 normal ) {
	return Vector3(0.f);
}
