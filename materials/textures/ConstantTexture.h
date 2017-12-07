#ifndef _CONSTANT_TEXTURE_H_
#define _CONSTANT_TEXTURE_H_

#include "Texture.h"

class ConstantTexture : public Texture {
	public:
		ConstantTexture();
		ConstantTexture(RGB color_) : color(color_) {};
		~ConstantTexture();
		Vector3 value(float u, float v, const Vector3 &p) override{
			return color;
		}

	private:
		RGB color;
};

#endif