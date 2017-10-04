#include "LambertianShader.h"

LambertianShader::LambertianShader() {
  maxRef = 0;
}

LambertianShader::LambertianShader( int maxRef_ ) {
  maxRef = maxRef;
}

RGB LambertianShader::GetColor( Ray r_, World world ) {
  return GetColorAux(r_, world, maxRef);
}

RGB LambertianShader::GetColorAux(Ray r_, World world, int maxRef_ ) {
  HitRecord rec;
  if(maxRef_ <= 0){
    return RGB(1.0, 1.0, 1.0);
  }
  if(world.HitAnything(r_, rec)) {
    Ray difused (Point3(0, 0, 0), Vector3(0, 0, 0));
    rec.material->Diffusion(r_, difused, rec.hitPoint, rec.normal);
    RGB visColor = rec.material->refCoef * rec.material->properties;
    return visColor * GetColorAux(difused, world, maxRef_-1);
  } else {
    Vector3 unitDirection = UnitVector(r_.Direction());
    float t = 0.5 * (unitDirection.Y() + 1.0);
    return (1.0 - t)*RGB(1.0, 1.0, 1.0) + t*RGB(0.5, 0.7, 1.0);
  }
}