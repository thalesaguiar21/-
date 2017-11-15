#include "DefaultShader.h"


DefaultShader::DefaultShader(void) {
	set_shader_value(0.f);
}

DefaultShader::DefaultShader(float value) {
  set_shader_value(value);
}

RGB DefaultShader::OnHit(Ray r_, World world, HitRecord rec) {
  return OnHitAux(r_, world, rec, shader_value());
}

RGB DefaultShader::OnHitAux(Ray r_, World world, HitRecord rec, 
                            int shaderValue_) {
  if(shaderValue_ <= 0){
    return RGB(1.0);
  } else {
    Ray difused;
    rec.mat->Diffusion(r_, difused, rec.hit, rec.normal);
    RGB visColor = rec.mat->ref_coef() * rec.mat->prop();
    return visColor * OnHitAux(difused, world, rec, shaderValue_-1);
  }
}
