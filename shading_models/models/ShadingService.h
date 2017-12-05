#ifndef _SHADING_SERVICE_H_
#define _SHADING_SERVICE_H_

#include "../materials/Material.h"
#include "../../hitables/World.h"
#include "ShadingModel.h"
#include "BlinnPhongShadingModel.h"
#include "LambertianShadingModel.h"
#include "CoolToWarmShadingModel.h"
#include "NormalShadingModel.h"
#include "ShadingType.h"

class ShadingService {
	public:
		ShadingService(void);
		RGB Shader(Ray r_, World world);

	private:
	 ShadingModel *shadingModel_;
};

#include "ShadingService.cpp"

#endif