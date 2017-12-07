#ifndef _BLINNPHONG_MAT_H_
#define _BLINNPHONG_MAT_H_

#include <algorithm>

#include "Material.h"

class BlinnPhong : public Material {
	public:
		BlinnPhong( void );
		BlinnPhong( RGB diffuse_, RGB specular_, Vector3 properties_ );
		bool Scatter( Ray incident, const HitRecord rec, Vector3 &attenuation, Ray &scattered ) override;

		RGB diffuse() const { return diffuse_; };
		void set_diffuse(RGB value) { diffuse_ = value; };
		RGB specular() const { return specular_; };
		void set_specular(RGB value) { specular_ = value; };
		Vector3 prop() const { return prop_; };
		void set_prop(Vector3 value) { prop_ = value; };
		
	private:
		Vector3 prop_;
		RGB diffuse_;
		RGB specular_;
};

#include "BlinnPhong.inl"

#endif
