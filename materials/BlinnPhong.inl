#include "BlinnPhong.h"

BlinnPhong::BlinnPhong ( Vector3 albedo_, float kd_, float ks_,
												 Vector3 diffuse_, Vector3 spec_ ) {
	kd = max(kd_, 0.0);
	ks = max(ks_, 0.0);
	diffuse = diffuse_;
	spec = spec_;
	properties = albedo_;
}

BlinnPhong::BlinnPhong ( Vector3 albedo, float absorption ) {
	//
}

bool BlinnPhong::Diffusion( Ray incident, Ray &diffused, Point3 hitPoint, Vector3 normal ) {
	return true;
}

Vector3 BlinnPhong::Reflect( Vector3 incident, Vector3 normal ) {

	return Vector3(0,0,0);
}