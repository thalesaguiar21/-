#ifndef _BLINNPHONG_MAT_H_
#define _BLINNPHONG_MAT_H_

#include "Material.h"

class BlinnPhong : public Material {
	public:
		BlinnPhong( void );
		BlinnPhong( RGB diffuse_, RGB specular_, float ka, float kd, float ks, float power );
	  bool Scatter( Ray incident, const HitRecord rec, Vector3 &attenuation, Ray &scattered ) override;

	protected:
	  Vector3 Reflect( Vector3 incident, Vector3 normal ) override;
};

#include "BlinnPhong.inl"

#endif
