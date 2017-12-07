#ifndef _NORMALTOCOLOR_H_
#define _NORMALTOCOLOR_H_

class NormalToColor : public Shader {
	public:
		NormalToColor(void);
		NormalToColor(float value);
		RGB Color(Ray r_, World world, int depth) override;
};

#include "NormalToColor.inl"

#endif
