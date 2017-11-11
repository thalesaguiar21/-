#include "DefaultShader.h"


DefaultShader::DefaultShader(void) {
	shaderValue = 0;
}

DefaultShader::DefaultShader(float value) {
  shaderValue = std::max(0.f, value);
}

RGB DefaultShader::GetColor(Ray r_, World world) {
  return GetColorAux(r_, world, shaderValue);
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
