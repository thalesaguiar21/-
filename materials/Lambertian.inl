#include "Lambertian.h"


Lambertian::Lambertian( Vector3 albedo, float absortion ) {
	prop = albedo;
	refCoef = absortion;
}

bool Lambertian::Diffusion( Ray incident, Ray &diffused, Point3 hitPoint,
														Vector3 normal ) {
	Vector3 target = hitPoint + normal + Reflect(incident.Direction(), normal);
	diffused = Ray(hitPoint, target - hitPoint);
	return true;
}

Vector3 Lambertian::Reflect( Vector3 incident, Vector3 normal ) {
	Vector3 p;
	do {
		p = 2.0 * (Vector3(drand48(), drand48(), drand48()) - Vector3(1.0, 1.0, 1.0));
	} while (dot(p, p) >= 1.0);
	return p;
}
