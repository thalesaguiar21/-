#ifndef _NORMALTOCOLOR_H_
#define _NORMALTOCOLOR_H_

#include "../utils/Vec3.h"
#include "../utils/Ray.h"

#include "../scene/Scene.h"

#include "Shader.h"

class NormalToColor : public Shader
{
private:
	// True uses the -b + root, and false use -b - root.
	bool rootToUse;

public:
	NormalToColor (bool rootToUse_ = false)
	{
		rootToUse = rootToUse_;
	}

	/* Take the intersection between the given Ray and the objects in the scene
	   create a normal vector and from this a color.

	   @param Ray The ray being shooted at the scene.
	   @param Image The parameters of the img.
	   @param Scene A scene with a list of actors
	   @return RGB The color created from the normal vector.	*/
	RGB getColor(Point3 surfacePoint, Point3 origin) override
	{
		RGB color (0.0, 0.0, 0.0);
		Vec3 normal = unit_vector(surfacePoint - origin);
		color = 0.5 * (normal + Vec3(1.0, 1.0, 1.0));
		return color;
	}
};

#endif
