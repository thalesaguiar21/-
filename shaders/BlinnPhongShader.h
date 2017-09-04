#ifndef _BLINNPHONGSHADER_H_
#define _BLINNPHONGSHADER_H_

#include "Shader.h"

class BlinnPhongShader : public Shader
{
public:
	RGB getColor(const Ray & r_, Image img, Scene scene) override 
	{
		return RGB(0, 0, 0);
	}
};

#endif