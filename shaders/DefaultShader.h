#ifndef _DEFAULTSHADER_H_
#define _DEFAULTSHADER_H_

class DefaultShader : public Shader {
	public:
		DefaultShader (void);
		DefaultShader(float value);
  	RGB Color(Ray r_, World world, int depth) override;
};

#include "DefaultShader.inl"

#endif