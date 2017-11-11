#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "../../utility/Vector3.h"
#include "../../utility/Ray.h"
#include "../../utility/Angles.h"

using namespace utils;

class Light {
	public:
		Light( void );
		Light(Vector3 origin, float intensity);

		virtual bool IsIlluminating(Point3 point);
		virtual Ray GetShadowRay(Point3 surface);

		Vector3 origin() const { return origin_; };
		void set_origin(Vector3 value) { origin_ = value; };
		float intensity() const {return intensity_; };
		void set_intensity(float value) { intensity_ = value; };

	private:
		Vector3 origin_;
		float intensity_;
};

#include "Light.inl"

#endif
