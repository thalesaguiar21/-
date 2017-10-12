#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include "../utility/Vector3.h"
#include "../utility/Ray.h"

using utils::Vector3;
using utils::Ray;

class Material {
	public:
		float refCoef;
		Vector3 properties;
		RGB diffuseColor;
		RGB specularColor;
		bool virtual Diffusion( Ray incident, Ray &diffused, Point3 hitPoint,
													  Vector3 normal ) = 0;
	protected:
 		Vector3 virtual Reflect( Vector3 incident, Vector3 normal ) = 0;
};

#endif
