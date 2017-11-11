#include "NormalToColor.h"

NormalToColor::NormalToColor( void ) {
	shaderValue  = 0;
}

NormalToColor::NormalToColor(float value) {
	shaderValue = std::max(0.f, value);
}

RGB NormalToColor::GetColor(Ray t_, World world) {
	HitRecord record;
	if(world.HitAnything(t_, record)){
		return record.normal;
	} else {
		return RGB (0, 0, 0);
	}
}