#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "../utility/Vector3.h"

using utils::Vector3;

class Light {
	public:
		Vector3 Origin;
		float Intensity;

		Light( void ) {
			// nothing
		}

		Light( Vector3 origin, float intensity ) {
			Origin = origin;
			Intensity = intensity;
		}

		bool virtual IsIlluminating( Point3 point ) {
			return true;
		}

		Ray virtual GetShadowRay( Point3 surface ) {
			return Ray(surface, Origin);
		}
};

#endif
