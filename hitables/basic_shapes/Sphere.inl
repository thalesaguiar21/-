#include "Sphere.h"

Sphere::Sphere( void ) {
  origin = Point3(0, 0, 0);
  radius = 0.f;
}

float Sphere::Discriminant(Ray r_, float &a, float &b, float &c) {
  Vector3 oc = r_.origin - origin;
  a = dot(r_.Direction(), r_.Direction());
  b = dot(oc, r_.Direction());
  c = dot(oc, oc) - radius*radius;
  float discriminant = b*b - a*c;
  return discriminant;
}

Sphere::Sphere( Point3 center_, float radius_, Material *material_ ) {
  origin = center_;
  radius = radius_;
  material = material_;
}

bool Sphere::Hit( Ray r_, HitRecord &rec, float minHit, float maxHit ) {
  float A, B, C;
  float discriminant = Discriminant(r_, A, B, C);
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
