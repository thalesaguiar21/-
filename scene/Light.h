#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "../utility/Vector3.h"

using utils::Vector3;

class Light {
	public:
		Vector3 DiffuseColor;
		Vector3 SpecularColor;
		Vector3 Origin;
		Vector3 Direction;
		Vector3 Intensity;
};

#endif
