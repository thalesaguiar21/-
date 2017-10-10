#include "BlinnPhongShader.h"

BlinnPhongShader::BlinnPhongShader( void ) {
	//
}

BlinnPhongShader::BlinnPhongShader( float power_ ) {
	power = std::max(0.f, power_);
}

RGB BlinnPhongShader::GetColor( Ray r_, World world ) {

	HitRecord rec;
	RGB ambient (1.0, 1.0, 1.0);
	if(world.HitAnything(r_, rec)) {
		RGB color(0.0, 0.0, 0.0);
		for(int i = 0; i < world.lights.size(); i++) {
			HitRecord tmp;
			// L
			auto lightRay = UnitVector(world.lights[i]->Origin - rec.hitPoint);
			// V
			auto viewDir = UnitVector(r_.origin - rec.hitPoint);
			// H
			auto halfWay = UnitVector(viewDir + lightRay);

			float max = std::max(0.f, dot(rec.normal, lightRay));
			auto diffuse = rec.material->properties.X() * max * rec.material->diffuseColor;

			auto reverseRay = Ray(world.lights[i]->Origin, rec.hitPoint);
			if(world.HitAnything(reverseRay, tmp)) {
				float hitToLight = UnitVector(world.lights[i]->Origin - rec.hitPoint).Length();
				float hitToSurface = UnitVector(tmp.hitPoint - rec.hitPoint).Length();
				if(hitToSurface < hitToLight) {
					color += diffuse;
				} else {
					max = std::max(0.f, dot(rec.normal, halfWay));
					auto specular = rec.material->properties.Y() * std::pow(max, power) * rec.material->specularColor;
					color += (rec.material->properties.Z() * ambient) + specular + diffuse;
				}
			} else {
				max = std::max(0.f, dot(rec.normal, halfWay));
				auto specular = rec.material->properties.Y() * std::pow(max, power) * rec.material->specularColor;
				color += (rec.material->properties.Z() * ambient) + specular + diffuse;
			}
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
