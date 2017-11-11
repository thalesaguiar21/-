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
  	BlinnPhongShader(void);
  	BlinnPhongShader(float power);
    RGB GetColor(Ray r_, World world);
};

#include "BlinnPhongShader.inl"

#endif
