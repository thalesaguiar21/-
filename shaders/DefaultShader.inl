#include "DefaultShader.h"


DefaultShader::DefaultShader(void) {
	//
}

DefaultShader::DefaultShader(float value) {
  //
}

RGB DefaultShader::Color(Ray r_, World world, int depth) {
  HitRecord tmp;
  if(world.HitAnything(r_, tmp)) {
    Ray scaterred;
    Vector3 attenuation;
    if(depth > 0 && tmp.mat->Scatter(r_, tmp, attenuation, scaterred)) {
      return attenuation * Color(scaterred, world, depth-1);
    } else {
      return RGB(0);
    }
  } else {
    return BackgroundColor(r_);
  }
}
