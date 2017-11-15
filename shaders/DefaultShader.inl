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
    return RGB(1.0);
  }
  if(world.HitAnything(r_, rec)) {
    Ray difused;
    rec.mat->Diffusion(r_, difused, rec.hit, rec.normal);
    RGB visColor = rec.mat->ref_coef() * rec.mat->prop();
    return visColor * GetColorAux(difused, world, shaderValue_-1);
  } else {
    return BackgroundColor(r_, RGB(1.0, 1.0, 1.0), RGB(0.7, 0.5, 1.0));
  }
}
