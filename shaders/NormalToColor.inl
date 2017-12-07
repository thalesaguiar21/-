#include "NormalToColor.h"

NormalToColor::NormalToColor( void ) {
	//
}

NormalToColor::NormalToColor(float value) {
	// 
}

RGB NormalToColor::Color(Ray t_, World world, int depth) {
	HitRecord rec;
	if(world.HitAnything(t_, rec)) 
		return rec.normal;
	else
		return BackgroundColor(t_);
}

