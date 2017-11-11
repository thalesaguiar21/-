#ifndef _SHADER_H_
#define _SHADER_H_

#include "../utility/Vector3.h"
#include "../hitables/World.h"

using utils::Vector3;

class Shader {
  public:
    virtual RGB GetColor(Ray r_, World world) = 0;

    float shader_value() const { return shader_value_; };
    void set_shader_value(float value) { shader_value_ = value; };
  private:
    float shader_value_;
};

#endif
