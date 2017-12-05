#include "Shader.h"

RGB Shader::Color(Ray r_, World world) {
  HitRecord rec;
  if(world.HitAnything(r_, rec)) {
  	Ray scattered;
  	Vector3 attenuation;
  	if(rec.mat->Scatter(r_, rec, attenuation, scattered))
      return OnHit(scattered, world, rec);
  } else {
    return BackgroundColor(r_, RGB(1.0, 1.0, 1.0), RGB(0.5, 0.7, 1.0));
  }
}

RGB Shader::BackgroundColor(Ray r_, RGB top, RGB bottom) {
  Vector3 unit_direction = UnitVector(r_.Direction());
  float t = 0.5 * (unit_direction.Y() + 1.0);
  return (1.0 - t)*top + t*bottom;
}