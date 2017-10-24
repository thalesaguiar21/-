#include "CoolToWarm.h"

RGB CoolToWarm::GetColor( Ray r_, World world ) {
  HitRecord rec;
	RGB ambient (1.0, 1.0, 1.0);
	if(world.HitAnything(r_, rec)) {
		RGB color (0,0,0);
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

				float difCoef = std::max(0.f, dot(rec.normal, lightRay));
				auto diffuse = rec.material->prop.X() * difCoef * rec.material->diffCol;
        float specCoef = std::max(0.f, dot(halfWay, rec.normal));
        auto specular = rec.material->prop.Y() *specCoef * rec.material->specCol;
        float angle = fabs(dot(UnitVector(rec.normal), UnitVector(r_.Direction())));
        if(angle < 0.30){
          return RGB(0,0,0);
        }
        auto kw = (1.0 + dot(UnitVector(rec.normal), lightRay)) / 2.0;
        color += kw*diffuse + (1-kw)*specular;

				auto shadowRay =  lights[i]->GetShadowRay(rec.hitPoint);
				if(!world.HitAnything(shadowRay, tmp)) {
          color += kw*diffuse + (1-kw)*specular;
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
