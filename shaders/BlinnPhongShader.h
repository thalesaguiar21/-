#ifndef _BLINNPHONGSHADER_H_
#define _BLINNPHONGSHADER_H_

#include "Shader.h"

class BlinnPhongShader : public Shader
{
public:
	RGB getColor(Point3 surfacePoint, Point3 originne) override
	{
		return RGB(0, 0, 0);
	}
};

#endif
