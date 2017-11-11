#include "BlinnPhongShader.h"

BlinnPhongShader::BlinnPhongShader( void ) {
	shaderValue = 0;
}

BlinnPhongShader::BlinnPhongShader(float value) {
	shaderValue = std::max(0.f, value);
}

RGB BlinnPhongShader::GetColor( Ray r_, World world ) {

	HitRecord rec;
	RGB ambient (0.8, 0.3, 0.5);
	if(world.HitAnything(r_, rec)) {
		RGB color = rec.material->prop.Z() * ambient;
		vector<Light*> lights = world.lights;
		for(int i = 0; i < lights.size(); i++) {
			if(lights[i]->IsIlluminating(rec.hitPoint)){
				HitRecord tmp;
				// L
				auto lightRay = UnitVector(lights[i]->origin() - rec.hitPoint);
				// V
				auto viewDir = UnitVector(r_.origin - rec.hitPoint);
				// H
				auto halfWay = UnitVector(viewDir + lightRay);
				float nlDot = std::max(0.000001f, dot(rec.normal, lightRay));
				auto diffuse = rec.material->prop.X() * nlDot * rec.material->diffCol;
				auto shadowRay =  lights[i]->GetShadowRay(rec.hitPoint);

				if(!world.HitAnything(shadowRay, tmp)) {
					float nhDot = std::max(0.000001f, dot(rec.normal, halfWay));
					auto specular = rec.material->prop.Y() * std::pow(nhDot, shaderValue) * rec.material->specCol;
					color += specular + diffuse;
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
