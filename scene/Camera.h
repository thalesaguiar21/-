#ifndef _CAMERA_H_
#define _CAMERA_H_

#define PI 3.141592

#include "../utility/Vector3.h"
#include "../utility/Ray.h"

using namespace utils;

using utils::Vector3;

class Camera {
	protected:
		Point3 from;
		Point3 at;
		Vector3 vup;
		Vector3 lowerLeftCorner;
		Vector3 u;
		Vector3 v;
		Vector3 w;
		Vector3 horizontal;
		Vector3 vertical;
		float lensRadius;

	public:

		virtual Ray shootRay(float s, float t) = 0;
};

#endif