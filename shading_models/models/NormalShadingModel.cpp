#include "NormalShadingModel.h"

NormalShadingModel::NormalShadingModel() {
	// Nothing
}

RGB NormalShadingModel::Color(Ray r_, World world, HitRecord &rec) {
	return rec.normal;
}