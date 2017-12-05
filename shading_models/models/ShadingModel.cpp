#include "ShadingModel.h"

RGB ShadingModel::BackgroundColor(Ray r_, RGB top, RGB bottom) {
  Vector3 unit_direction = UnitVector(r_.Direction());
  float t = 0.5 * (unit_direction.Y() + 1.0);
  return (1.0 - t)*top + t*bottom;
}