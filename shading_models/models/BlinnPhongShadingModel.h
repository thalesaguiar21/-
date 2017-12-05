#ifndef _BLINNPHONG_SHADING_MODEL_H_
#define _BLINNPHONG_SHADING_MODEL_H_

#include "ShadingModel.h"
#include "../materials/BlinnPhong.h"

class BlinnPhongShadingModel : public ShadingModel {
	public:		
		BlinnPhongShadingModel(void);
		BlinnPhongShadingModel(float power);
    RGB Color(Ray r_, World world, HitRecord &rec) override;
  	float power() const { return power_; }

  private:
  	float const MAX_POWER = 100.f;
  	float const MIN_POWER = 0.f;
    float const SHADOW_ERROR = 0.00001f;
  	float power_;
};

#include "BlinnPhongShadingModel.cpp"

#endif