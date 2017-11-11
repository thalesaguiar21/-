#include "DefaultShader.h"


DefaultShader::DefaultShader(void) {
	set_shader_value(0.f);
}

DefaultShader::DefaultShader(float value) {
  set_shader_value(value);
}

RGB DefaultShader::GetColor(Ray r_, World world) {
  return GetColorAux(r_, world, shader_value());
}

RGB DefaultShader::GetColorAux(Ray r_, World world, int shaderValue_) {
	HitRecord rec;
  if(shaderValue_ <= 0){
    return RGB(1.0, 1.0, 1.0);
  }
  if(world.HitAnything(r_, rec)) {
    Ray difused;
    rec.material->Diffusion(r_, difused, rec.hitPoint, rec.normal);
    RGB visColor = rec.material->refCoef * rec.material->prop;
    return visColor * GetColorAux(difused, world, shaderValue_-1);
  } else {
    Vector3 unitDirection = UnitVector(r_.Direction());
    float t = 0.5 * (unitDirection.Y() + 1.0);
    return (1.0 - t)*RGB(1.0, 1.0, 1.0) + t*RGB(0.5, 0.7, 1.0);
  }
}
