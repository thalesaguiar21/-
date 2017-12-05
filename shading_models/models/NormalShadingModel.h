#ifndef _NORMAL_SHADING_MODEL_H_
#define _NORMAL_SHADING_MODEL_H_

#include "ShadingModel.h"

class NormalShadingModel : public ShadingModel {
	public:	
		NormalShadingModel(void);
  	RGB Color(Ray r_, World world, HitRecord &rec) override;
};

#include "NormalShadingModel.cpp"

#endif