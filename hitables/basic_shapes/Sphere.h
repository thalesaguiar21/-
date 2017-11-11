#ifndef _SPHERE_H_
#define _SPHERE_H_

#include "../../utility/Vector3.h"
#include "../../utility/Ray.h"
#include "../../materials/Material.h"
#include "../Hitable.h"
#include <cmath>

using utils::Vector3;
using utils::Ray;

class Sphere : public Hitable {
  public:
    Sphere(void);
    Sphere(Point3 center_, float radius_, Material *material_);
    bool Hit(Ray r_, HitRecord &rec, float minHit, float maxHit) override;

    float radius() const { return radius_; };
    void set_radius(float value) { radius_ = value; };

  private:
    float Discriminant(Ray r_, float &a, float &b, float &c);

    float radius_;
};


#include "Sphere.inl"

#endif
