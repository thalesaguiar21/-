#include "BlinnPhongShader.h"

BlinnPhongShader::BlinnPhongShader( void ) {
	//
}

BlinnPhongShader::BlinnPhongShader( Vector3 reflections ) {
	//
}

RGB BlinnPhongShader::GetColor( Ray r_, World world ) {

	HitRecord rec;
	RGB test (0.0, 1.0, 1.0);
	//bool
	float power = 400.0;
	if(world.HitAnything(r_, rec)) {
		RGB color(0.0, 0.0, 0.0);
		for(int i = 0; i < world.lights.size(); i++) {
			HitRecord tmp;
			// L
			//auto lightRay = Ray(rec.hitPoint, world.lights[i]->Origin);
			auto lightRay = UnitVector(world.lights[i]->Origin - rec.hitPoint);
			//std::cout << "HEY" << std::endl;
			// V
			auto viewDir = UnitVector(r_.origin - rec.hitPoint);
			auto halfWay = UnitVector(viewDir + lightRay);
			float max = std::max(0.f, dot(rec.normal, lightRay));
			auto diffuse = 0.5 * max * test;
			max = std::max(0.f, dot(rec.normal, halfWay));
			auto specular = 1.0 * std::pow(max, power) * RGB(1.0, 1.0, 1.0);

			color += (0.1 * test) + specular + diffuse;
			//std::cout << color << std::endl;
		}
		return color;
	} else {
		Vector3 unitDirection = UnitVector(r_.Direction());
    float t = 0.5 * (unitDirection.Y() + 1.0);
    return (1.0 - t)*RGB(1.0, 1.0, 1.0) + t*RGB(0.5, 0.7, 1.0);
	}
}


RGB BlinnPhongShader::BlinnColor() {
	RGB color (0, 0, 0);

	return color;
}