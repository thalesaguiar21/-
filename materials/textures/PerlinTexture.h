#ifndef _PERLIN_TEXTURE_H_
#define _PERLIN_TEXTURE_H_

#include "Texture.h"
#include "../../utility/Perlin.h"
using utils::Perlin;

class PerlinTexture : public Texture {
	public:
		PerlinTexture(void) {}
		PerlinTexture(float scale_) {
			scale = scale_;
		}
		Vector3 Value(float u, float v, const Vector3 &p) override {
			Vector3 pAux = p;
			return Vector3(1.0)*0.5*(1+sin(scale*pAux.Z() + 10*perlin.turb(pAux)));
		}

		Perlin perlin;
		float scale;
};

#endif