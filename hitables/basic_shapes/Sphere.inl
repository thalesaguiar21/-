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
      rec.normal = (rec.hit - origin()) / radius();
      rec.mat = material();
      return true;
    }
    root = (-B + sqrt(discriminant))/A;
    if(root < maxHit && root > minHit) {
      rec.root = root;
      rec.hit = r_.PointAt(rec.root);
      rec.normal = (rec.hit - origin()) / radius();
      rec.mat = material();
      return true;
    }
  }
  return false;
}


Hitable* Sphere::Translate(Vector3 target) {
  glm::vec4 trasnslade_vec (target.X(), target.Y(), target.Z(), 1);
  glm::vec3 translation (origin().X(), origin().Y(), origin().Z());
  glm::mat4 tMatrix = glm::translate(glm::mat4(1.0f), translation);
  glm::vec4 centerT = tMatrix * trasnslade_vec;
  
  Vector3 transladed_center (centerT[0], centerT[1], centerT[2]);
  return new Sphere(transladed_center, radius(), material());
}

Hitable* Sphere::Rotate(Vector3 angles) {
  return new Sphere(origin(), radius(), material());
}

Hitable* Sphere::Scale(Vector3 proportions) {
  return new Sphere();
}
