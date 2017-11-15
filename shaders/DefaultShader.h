#ifndef _DEFAULTSHADER_H_
#define _DEFAULTSHADER_H_

class DefaultShader : public Shader {
	public:
		DefaultShader (void);
		DefaultShader(float value);

  protected:
  	RGB OnHit(Ray r_, World world, HitRecord rec) override;
  	
 	private:
 		RGB OnHitAux(Ray r_, World world, HitRecord rec, int maxRef_);
};

#include "DefaultShader.inl"

#endif