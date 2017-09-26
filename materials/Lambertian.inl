#include "Lambertian.h"


namespace materials {

	Lambertian::Lambertian( Vector3 albedo, float absortion ) {
		properties = albedo;
		refCoef = absortion;
	}

	bool Lambertian::diffusion( Ray r_, Ray &diffused, Point3 hitPoint,
															Vector3 normal ) override {
		Vector3 target = hitPoint + normal + RandomInUnitSphere();
		diffused = (rec.hitPoint, target);
		return true;
	}
}
