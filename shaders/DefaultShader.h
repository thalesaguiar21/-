#ifndef _DEFAULTSHADER_H_
#define _DEFAULTSHADER_H_

class DefaultShader : public Shader {
	public:
		DefaultShader (void);
		DefaultShader(float value);
    RGB GetColor(Ray r_, World world) override;
 	private:
 		RGB GetColorAux(Ray r_, World world, int maxRef_);
};

#include "DefaultShader.inl"

#endif