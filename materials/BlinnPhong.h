#ifndef _BLINNPHONG_MAT_H_
#define _BLINNPHONG_MAT_H_

#include <algorithm>

#include "Material.h"

class BlinnPhong : public Material {
public:
	BlinnPhong( void );
	BlinnPhong( RGB diffuse_, RGB specular_, Vector3 properties_ );
	bool Scatter( Ray incident, const HitRecord rec, Vector3 &attenuation, Ray &scattered ) override;
};

#include "BlinnPhong.inl"

#endif
