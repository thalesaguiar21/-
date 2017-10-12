#ifndef _SPOTLIGHT_H_
#define _SPOTLIGHT_H_

#include "Light.h"

class SpotLight : public Light {
public:
	float halfView;
};


#endif
