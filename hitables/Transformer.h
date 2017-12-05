#ifndef _TRANSFORMER_H_
#define _TRANSFORMER_H_

#include "../utility/Vector3.h"
#include "Hitable.h"
// vec3, vec4, ivec4, mat4
#include "../external/glm/glm.hpp"
// translate, rotate, scale, perspective
#include "../external/glm/gtc/matrix_transform.hpp"


class Transformer {
	public:
		Transformer();

		Hitable* Translade(Vector3 target, Hitable *original);
		Hitable* Rotate(Vector3 angles, Hitable *original);
		Hitable* Scale(Vector3 propotions, Hitable *original);
	private:
};

#include "Transformer.inl"

#endif // _TRANSFORMER_H_