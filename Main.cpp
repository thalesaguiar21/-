#include <iostream>

#include "utility/Vector3.h"
#include "utility/Ray.h"
#include "scene/Camera.h"
#include "hitables/HitRecord.h"
#include "hitables/Hitable.h"
#include "hitables/basic_shapes/Sphere.h"

using namespace utils;
using basicShapes::Sphere;

int main( int argc, char *argv[] ) {
  Sphere s = Sphere();
  HitRecord rec;
  if( s.Hit(Ray(Point3(0,0,0), Point3(0,0,0)), rec) ){
    std::cout << "HIT!" << std::endl;
  }
  return 0;
}
