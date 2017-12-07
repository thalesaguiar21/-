#include "CoolToWarm.h"

CoolToWarm::CoolToWarm(void) {
	power_ = 0.f;
}

CoolToWarm::CoolToWarm(float value) {
	power_ = value;
}

RGB CoolToWarm::Color(Ray r_, World world, int depth) {
	HitRecord rec;
	RGB ambient (1.0, 1.0, 1.0);
	RGB color (0,0,0);
	if(world.HitAnything(r_, rec)) {
		BlinnPhong *mat = dynamic_cast<BlinnPhong*>(rec.mat);
		vector<Light*> lights = world.lights;
		for(int i = 0; i < lights.size(); i++) {
			if(lights[i]->IsIlluminating(rec.hit)){
				HitRecord tmp;
				// L
				auto lightRay = UnitVector(lights[i]->origin() - rec.hit);
				// V
				auto viewDir = UnitVector(r_.origin - rec.hit);
				// H
				auto halfWay = UnitVector(viewDir + lightRay);

				float difCoef = std::max(0.f, dot(rec.normal, lightRay));
				auto diffuse = mat->prop().X() * difCoef * mat->diffuse();
	      float specCoef = std::max(0.f, dot(halfWay, rec.normal));
	      auto specular = mat->prop().Y() *specCoef * mat->specular();
	      float angle = fabs(dot(UnitVector(rec.normal), UnitVector(r_.Direction())));
	      if(angle < 0.30){
	        return RGB(0,0,0);
	      }
	      auto kw = (1.0 + dot(UnitVector(rec.normal), lightRay)) / 2.0;
	      color += kw*diffuse + (1-kw)*specular;

				auto shadowRay =  lights[i]->GetShadowRay(rec.hit);
				if(!world.HitAnything(shadowRay, tmp)) {
	        color += kw*diffuse + (1-kw)*specular;
				}
			}
		}	
	} else {
		return BackgroundColor(r_);
	}
	
	return color;
}
