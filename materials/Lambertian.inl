#include "Lambertian.h"


namespace materials {

	Lambertian::Lambertian( Vector3 albedo, float absortion ) {
		properties = albedo;
		refCoef = absortion;
	}

	bool Lambertian::diffusion( Ray r_, Ray &diffused, Point3 hitPoint,
															Vector3 normal ) {
		Vector3 target = hitPoint + normal + RandomInUnitSphere();
		diffused = Ray(hitPoint, target);
		return true;
	}
}
