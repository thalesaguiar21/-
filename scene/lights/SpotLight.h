#ifndef _SPOTLIGHT_H_
#define _SPOTLIGHT_H_

#include "Light.h"

class SpotLight : public Light {
	public:
		SpotLight(void);
		SpotLight(Point3 origin_, Point3 dir, float intensity, float radius, 
							float fov_);

		bool IsIlluminating( Point3 point ) override;
		Ray GetShadowRay( Point3 surface ) override;

		float radius() const { return radius_; };
		void set_radius(float value) { radius_ = value; };
		float aperture_angle() const { return aperture_angle_; };
		void set_aperture_angle(float value) { aperture_angle_ = rad(value); };
		Vector3 direction() const { return direction_; };
		void set_direction(Vector3 value) { direction_ = value; };

	private:
		float radius_;
		float aperture_angle_;
		Vector3 direction_;
};

#include "SpotLight.inl"

#endif
