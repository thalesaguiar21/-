#ifndef _DEPTHMAP_H_
#define _DEPTHMAP_H_

#include "Shader.h"

class DepthMap : public Shader {
	RGB getColor(Point3 surfacePoint, Point3 origin) override
	{
		return RGB(0, 0, 0);
	}
};

#endif
