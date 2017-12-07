#ifndef _TEXTURE_H_
#define _TEXTURE_H_

class Texture {
	public:
		virtual Vector3 Value(float u, float v, const Vector3 &p) = 0;
};

#endif