#include "Sphere.h"

Sphere::Sphere( void ) {
  set_origin(Vector3(0.f));
  radius_ = 0.f;
}

Sphere::Sphere( Point3 center_, float rad_, Material *mat_ ) {
  set_origin(center_);
  set_material(mat_);
  radius_ = rad_;
}

float Sphere::Discriminant(Ray r_, float &a, float &b, float &c) {
  Vector3 oc = r_.origin - origin();
  a = dot(r_.Direction(), r_.Direction());
  b = dot(oc, r_.Direction());
  c = dot(oc, oc) - radius()*radius();
  float discriminant = b*b - a*c;
  return discriminant;
}

bool Sphere::Hit( Ray r_, HitRecord &rec, float minHit, float maxHit ) {
  float A, B, C;
  float discriminant = Discriminant(r_, A, B, C);
  if(discriminant > 0) {
    float root = (-B - sqrt(discriminant))/A;
    if(root < maxHit && root > minHit) {
      rec.root = root;
      rec.hit = r_.PointAt(rec.root);
      rec.normal = UnitVector(rec.hit - origin());
      rec.mat = material();
      return true;
    }
    root = (-B + sqrt(discriminant))/A;
    if(root < maxHit && root > minHit) {
      rec.root = root;
      rec.hit = r_.PointAt(rec.root);
      rec.normal = UnitVector(rec.hit - origin());
      rec.mat = material();
      return true;
    }
  }
  return false;
}
