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
		RGB color (0,0,0);//= rec.material->prop.Z() * ambient;
		vector<Light*> lights = world.lights;
		for(int i = 0; i < lights.size(); i++) {
			if(lights[i]->IsIlluminating(rec.hitPoint)){
				HitRecord tmp;
				// L
				auto lightRay = UnitVector(lights[i]->Origin - rec.hitPoint);
				// V
				auto viewDir = UnitVector(r_.origin - rec.hitPoint);
				// H
				auto halfWay = UnitVector(viewDir + lightRay);
				float max = std::max(0.f, dot(rec.normal, lightRay));
				auto diffuse = rec.material->prop.X() * max * rec.material->diffCol;
				auto shadowRay =  lights[i]->GetShadowRay(rec.hitPoint);//(rec.hitPoint, lights[i]->Origin);
				if(!world.HitAnything(shadowRay, tmp)) {
					max = std::max(0.f, dot(rec.normal, halfWay));
					auto specular = rec.material->prop.Y() * std::pow(max, power) * rec.material->specCol;
					color += (rec.material->prop.Z() * ambient) + specular + diffuse;
				}
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
