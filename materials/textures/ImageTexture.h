#ifndef _IMAGE_TEXTURE_H_
#define _IMAGE_TEXTURE_H_

#include "Texture.h"

class ImageTexture : public Texture {
	public:
		ImageTexture() {}
		ImageTexture(unsigned char *pixels, int A, int B) {
			data = pixels;
			nx = A;
			ny = B;
		}

		Vector3 Value(float u, float v, const Vector3 &p) override {
			Vector3 pAux = p;
			int i = ( u)*nx;
			int j = (1-v)*ny-0.001;
			if(i < 0) i = 0;
			if(j < 0) j = 0;
			if(i > nx-1) i = nx-1;
			if(j > ny-1) j = ny-1;
			float r = int(data[3*i + 3*nx*j]) / 255.0;
			float g = int(data[3*i + 3*nx*j+1]) / 255.0;
			float b = int(data[3*i + 3*nx*j+2]) / 255.0;
			return Vector3(r, g, b);
		}
		

		unsigned char *data;
		int nx, ny;
};

#endif