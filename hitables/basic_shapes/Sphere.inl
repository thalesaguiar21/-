#include "Sphere.h"

namespace basicShapes {
  Sphere::Sphere( void ) {
    origin = Point3(0, 0, 0);
    radius = 0.f;
  }

  Sphere::Sphere( Point3 center_, float radius_, Material *material_ ) {
    origin = center_;
    radius = radius_;
    material = material_;
  }

  bool Sphere::Hit( Ray r_, HitRecord &rec, float minHit, float maxHit ) {
    Vector3 oc = r_.origin - origin;
    float A = dot(r_.Direction(), r_.Direction());
    float B = dot(oc, r_.Direction());
    float C = dot(oc, oc) - radius*radius;
    float discriminant = B*B - A*C;
    if(discriminant > 0) {
      float root = (-B - sqrt(discriminant))/A;
      if(root < maxHit && root > minHit) {
        rec.root = root;
        rec.hitPoint = r_.PointAt(rec.root);
        rec.normal = UnitVector(rec.hitPoint - origin);
        rec.material = material;
        return true;
      }
      root = (-B + sqrt(discriminant))/A;
      if(root < maxHit && root > minHit) {
        rec.root = root;
        rec.hitPoint = r_.PointAt(rec.root);
        rec.normal = UnitVector(rec.hitPoint - origin);
        rec.material = material;
        return true;
      }
    }
    return false;
  }
}
