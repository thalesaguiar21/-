#ifndef _POINTLIGHT_H_
#define _POINTLIGHT_H_

#include "Light.h"

class PointLight : public Light {
	Point3 position;
	float DiffusePower;
	float SpecularPower;
};

#endif