#include "BlinnPhong.h"


BlinnPhong::BlinnPhong( void ) {
	//
}

BlinnPhong::BlinnPhong( RGB diffuse_, RGB specular_, Vector3 properties_ ) {
	diffuseColor = diffuse_;
	specularColor = specular_;
	properties = properties_;
}

bool BlinnPhong::Diffusion( Ray incident, Ray &diffused, Point3 hitPoint, Vector3 normal ) {
	return true;
}

Vector3 BlinnPhong::Reflect( Vector3 incident, Vector3 normal ) {
	return Vector3(0,0,0);
}