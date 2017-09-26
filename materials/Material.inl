#include "Material.h"

namespace materials {
	Vector3 RandomInUnitSphere() {
		Vector3 p;
		do
		{
			p = 2.0 * (Vector3(drand48(), drand48(), drand48()) - Vector3(1.0, 1.0, 1.0));
		} while (dot(p, p) >= 1.0);
		return p;
	}
}
