#include "BlinnPhong.h"


BlinnPhong::BlinnPhong( void ) {
	set_diffuse(RGB(0));
	set_specular(RGB(0));
	set_prop(Vector3(0.f, 0.f, 0.f));
	set_shader_value(1);
	shader = ShadingType::blinnPhong;
}

BlinnPhong::BlinnPhong( RGB diffuse_, RGB specular_, float ka, float kd, float ks, float power ) {
	set_diffuse(diffuse_);
	set_specular(specular_);
	set_prop(Vector3(ka, kd, ks));
	set_shader_value(power);
	shader = ShadingType::blinnPhong;
}

bool BlinnPhong::Scatter( Ray incident, const HitRecord rec, Vector3 &attenuation, Ray &scattered ) {
	scattered = incident;
	attenuation = Vector3(1.f);
	return true;
}

Vector3 BlinnPhong::Reflect( Vector3 incident, Vector3 normal ) {
	return Vector3(0.f);
}
