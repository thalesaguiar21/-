#ifndef _SHADER_H_
#define _SHADER_H_

#define SHADOW_ERROR 0.001

#include "../utility/Vector3.h"
#include "../hitables/World.h"

using utils::Vector3;

class Shader {
  public:
    virtual RGB Color(Ray r_, World world, int depth = 10) = 0;
    float shader_value() const { return shader_value_; };
    void set_shader_value(float value) { shader_value_ = value; };

  protected:
  	RGB BackgroundColor(Ray r_, RGB top, RGB bottom);
  	
  private:
    float shader_value_;
};

#include "Shader.inl"

#endif
