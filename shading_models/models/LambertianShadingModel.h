#ifndef _LAMBERTIAN_SHADING_MODEL_H_
#define _LAMBERTIAN_SHADING_MODEL_H_

#include "ShadingModel.h"

class LambertianShadingModel : public ShadingModel {
public:
	LambertianShadingModel(void);
	LambertianShadingModel(int reflections);
	int reflections() const { return reflections_; }
	RGB Color(Ray r_, World world, HitRecord &rec) override;  	

protected:
  RGB ColorAux(Ray r_, World world, HitRecord &rec, int ref);

private:
	int const MAX_REFLECTIONS = 30;
	int const MIN_REFLECTIONS = 1;
	int reflections_;
};

#include "LambertianShadingModel.cpp"

#endif