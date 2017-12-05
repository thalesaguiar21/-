#include "NormalToColor.h"

NormalToColor::NormalToColor( void ) {
	set_shader_value(0.f);
}

NormalToColor::NormalToColor(float value) {
	set_shader_value(value);
}

RGB NormalToColor::OnHit(Ray t_, World world, HitRecord rec) {
	return rec.normal;
}

