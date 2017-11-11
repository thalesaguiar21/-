#ifndef _BLINNPHONG_SHADER_H_
#define _BLINNPHONG_SHADER_H_

#include <iostream>
#include <algorithm>
#include <cmath>

#include "../utility/Vector3.h"
#include "../utility/Ray.h"
#include "../scene/lights/Light.h"
#include "Shader.h"

using utils::Vector3;
using utils::Ray;

class BlinnPhongShader : public Shader {
  public:
  	float power;
  	
  	BlinnPhongShader ( void );
    BlinnPhongShader( float power_ );
    RGB GetColor( Ray r_, World world );
    RGB BlinnColor( );
};

#include "BlinnPhongShader.inl"

#endif
