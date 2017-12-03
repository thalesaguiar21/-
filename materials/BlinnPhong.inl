#include "BlinnPhong.h"


BlinnPhong::BlinnPhong( void ) {
	//
}

BlinnPhong::BlinnPhong( RGB diffuse_, RGB specular_, Vector3 properties_ ) {
	set_diffuse(diffuse_);
	set_specular(specular_);
	set_prop(properties_);
}

bool BlinnPhong::Scatter( Ray incident, const HitRecord rec, Vector3 &attenuation, Ray &scattered ) {
	scattered = incident;
	attenuation = prop();
	return true;
}

Vector3 BlinnPhong::Reflect( Vector3 incident, Vector3 normal ) {
	return Vector3(0.f);
}
