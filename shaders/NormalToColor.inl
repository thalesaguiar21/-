#include "NormalToColor.h"

NormalToColor::NormalToColor( void ) {
	set_shader_value(0.f);
}

NormalToColor::NormalToColor(float value) {
	set_shader_value(value);
}

RGB NormalToColor::GetColor(Ray t_, World world) {
	HitRecord record;
	if(world.HitAnything(t_, record)){
		return record.normal;
	} else {
		return RGB (0, 0, 0);
	}
}