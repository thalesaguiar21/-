#ifndef _SHADING_MODEL_H_
#define _SHADING_MODEL_H_

#include "../../hitables/World.h"
#include "../materials/Material.h"
#include "../../hitables/HitRecord.h"

class ShadingModel {
	public:		
  	virtual RGB Color(Ray r_, World world, HitRecord &rec) = 0;
   	RGB BackgroundColor(Ray r_, RGB top, RGB bottom);    
};

#include "ShadingModel.cpp"

#endif