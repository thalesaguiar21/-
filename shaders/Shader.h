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

  protected:
  	RGB BackgroundColor(Ray r_, RGB top, RGB bottom) {
  		Vector3 unit_direction = UnitVector(r_.Direction());
	    float t = 0.5 * (unit_direction.Y() + 1.0);
	    return (1.0 - t)*top + t*bottom;
  	}
  	
  private:
    float shader_value_;
};

#endif
