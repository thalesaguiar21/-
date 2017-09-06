#ifndef _SHADER_H_
#define _SHADER_H_

#include "../utils/Vec3.h"
#include "../utils/Ray.h"
#include "../scene/Scene.h"


/* A Shader must inherit from this class and implement the method getColor.
	 This method is where the shader must provide a generated color. */
class Shader
{
public:
	virtual RGB getColor(Point3 surfacePoint, Point3 origin) = 0;
};

#endif
