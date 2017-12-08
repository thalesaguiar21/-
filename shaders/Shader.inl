#include "Shader.h"

RGB Shader::BackgroundColor(Ray r_, RGB top = RGB(1,1,1), RGB bottom = RGB(0.5,0.7,1.0)) {
  // Vector3 unit_direction = UnitVector(r_.Direction());
  // float t = 0.5 * (unit_direction.Y() + 1.0);
  // return (1.0 - t)*top + t*bottom;
	return RGB(0);
}