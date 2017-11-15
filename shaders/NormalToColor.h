#ifndef _NORMALTOCOLOR_H_
#define _NORMALTOCOLOR_H_

class NormalToColor : public Shader {
	public:
		NormalToColor(void);
		NormalToColor(float value);

	protected:
		RGB OnHit(Ray r_, World world, HitRecord rec) override;
};

#include "NormalToColor.inl"

#endif
