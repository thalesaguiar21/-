#include "Sphere.h"

namespace basicShapes {
  Sphere::Sphere( void ) {
    origin = Point3(0, 0, 0);
    radius = 0.f;
  }

  Sphere::Sphere( Point3 center_, float radius_ ) {
    origin = center_;
    radius = radius_;
  }

  bool Sphere::Hit( Ray r_, HitRecord &rec ) {
    Vector3 oc = r_.origin - origin;
    float A = dot(r_.Direction(), r_.Direction());
    float B = dot(oc, r_.Direction());
    float C = dot(oc, oc);
    float discriminant = B*B - A*C;
    if(discriminant > 0) {
      float root = (-B - sqrt(discriminant));
      if(root < 0.0) {
        root = (-B + sqrt(discriminant));
      }
      rec.root = root;
      rec.hitPoint = r_.PointAt(root);
      rec.normal = (rec.hitPoint - origin) / radius;
      return true;
    }
    return false;
  }
}
