#include "NormalToColor.h"

RGB NormalToColor::GetColor(Ray t_, World world) {
	HitRecord record;
	if(world.HitAnything(t_, record)){
		return record.normal;
	} else {
		return RGB (0, 0, 0);
	}
}