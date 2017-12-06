#include "LambertianShadingModel.h"

LambertianShadingModel::LambertianShadingModel(void) {
	reflections_ = MIN_REFLECTIONS;
}


LambertianShadingModel::LambertianShadingModel(int reflections) {
	if(reflections > MAX_REFLECTIONS) {
		reflections_ = MAX_REFLECTIONS;
	} else if(reflections < MIN_REFLECTIONS) {
		reflections_ = MIN_REFLECTIONS;
	} else {
		reflections_ = reflections;
	}
}


RGB LambertianShadingModel::Color(Ray r_, World world, HitRecord &rec) {
  return ColorAux(r_, world, rec, reflections());
}

RGB LambertianShadingModel::ColorAux(Ray r_, World world, HitRecord &rec, int ref) {
  
  HitRecord tmp;
  if(world.HitAnything(r_, tmp)) {
	  Ray scaterred;
	  Vector3 attenuation;
	  if(ref > 0 && rec.mat->Scatter(r_, tmp, attenuation, scaterred)) {
	  	return attenuation * ColorAux(scaterred, world, tmp, ref-1);
	  } else {
	  	return BackgroundColor(r_, RGB(0,1,0), RGB(0,0,1));
	  }
  } else {
  	return RGB(1);
  }
  
}