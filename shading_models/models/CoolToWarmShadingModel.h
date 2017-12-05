#ifndef _COOL_TO_WARM_SHADING_MODEL_H_
#define _COOL_TO_WARM_SHADING_MODEL_H_

#include "ShadingModel.h"

class CoolToWarmShadingModel : public ShadingModel {
	public:
		CoolToWarmShadingModel(void);
		CoolToWarmShadingModel(float power);
  	RGB Color(Ray r_, World world, HitRecord &rec) override;
  	float power() const { return power_; }

  private:
  	float const MAX_POWER = 100.f;
  	float const MIN_POWER = 0.f;
  	float power_;
};

#include "CoolToWarmShadingModel.cpp"

#endif