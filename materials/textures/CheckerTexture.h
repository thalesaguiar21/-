#ifndef _CHECKER_TEXTURE_H_
#define _CHECKER_TEXTURE_H_

#include "Texture.h"

class CheckerTexture : public Texture {
	public:
		CheckerTexture(Texture *odd_, Texture *even_) {
			odd = odd_;
			even = even_;
		}
		~CheckerTexture();
		Vector3 Value(float u, float v, const Vector3 &p) override{
			Vector3 tmp = 10 * p;
			float sines = sin(tmp.X()) * sin(tmp.Y()) * sin(tmp.Z());
			if(sines < 0) 
				return odd->Value(u,v,p);
			else
				return even->Value(u,v,p);
		}
	
	private:
		Texture *odd;
		Texture *even;	
};

#endif