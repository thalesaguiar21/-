#include "ShadingService.h"

ShadingService::ShadingService(void) {
	// TODO
}

RGB ShadingService::Shader(Ray r_, World world) {
	HitRecord rec;
	RGB result (0);
	if(world.HitAnything(r_, rec)) {
		float modelValue = rec.mat->shader_value();
		switch(rec.mat->shading_type()) {
			case ShadingType::blinnPhong:
				// std::cout << "BLINN" << std::endl;
				shadingModel_ = new BlinnPhongShadingModel(modelValue);
				break;
			case ShadingType::lambertian:
				shadingModel_ = new LambertianShadingModel(modelValue);
				break;
			case ShadingType::coolToWarm:
				shadingModel_ = new CoolToWarmShadingModel(modelValue);
				break;
			case ShadingType::normal:
				shadingModel_ = new NormalShadingModel();
				break;
			case ShadingType::metalic:
				// TODO
				break;
		}
		result = shadingModel_->Color(r_, world, rec);
	} else {
		RGB blue (0,0,1);
		RGB green (0,1,0);
		result = ShadingModel::BackgroundColor(r_, blue, green);
	}

	delete shadingModel_;
	return result;
}