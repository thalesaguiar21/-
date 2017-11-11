#ifndef _SPOTLIGHT_H_
#define _SPOTLIGHT_H_

#include "Light.h"

class SpotLight : public Light {
public:
	float Radius;
	float theta;
	Vector3 Direction;

	SpotLight( void );
	SpotLight( Point3 origin_, Point3 dir, float intensity, float radius, float fov_ );

	bool IsIlluminating( Point3 point ) override;
	Ray GetShadowRay( Point3 surface ) override;
};

#include "SpotLight.inl"

#endif
