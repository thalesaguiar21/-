#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "utility/Vector3.h"
#include "utility/Ray.h"
#include "scene/Camera.h"
#include "hitables/HitRecord.h"
#include "hitables/Hitable.h"
#include "hitables/basic_shapes/Sphere.h"
#include "hitables/World.h"

using namespace utils;
using namespace hitables;

using basicShapes::Sphere;

using std::cout;
using std::endl;
using std::string;
using std::flush;

RGB color( Ray r_, World world ) {
  HitRecord rec;
  if(world.HitAnything(r_, rec, 100.0)) {
    return 0.5 * (Vector3(1.0, 1.0, 1.0) + UnitVector(rec.normal));
  } else {
    Vector3 unitDirection = UnitVector(r_.Direction());
    float t = 0.5 * (unitDirection.Y() + 1.0);
    return (1.0 - t)*RGB(1.0, 1.0, 1.0) + t*RGB(0.5, 0.7, 1.0);
  }
}

int main( int argc, char *argv[] ) {
  int nx = 400;
  int ny = 200;
  std::ofstream file("../test.ppm");
  file << "P3\n";
  file << nx << " " << ny << "\n";
  file << "255\n";
  Camera cam (Point3(0,0,0), Point3(-2, -1, -1), Vector3(4, 0, 0), Vector3(0, 2, 0));
  std::vector<Hitable*> myHitables = { new Sphere(Point3(0, 0, -1.0), 0.3) };
  World world (myHitables);

  for(auto row=ny-1; row>=0; row--) {
    for(auto col=0; col<nx; col++) {
      float u = float(col) / float(nx);
      float v = float(row) / float(ny);
      Ray r = cam.ShootRay(u, v);
      RGB coloring = color(r, world);

      int ir = int(255.99 * coloring.R());
      int ig = int(255.99 * coloring.G());
      int ib = int(255.99 * coloring.B());

      file << ir << " " << ig << " " << ib << "\n";
    }
  }
  file.close();
  return 0;
}
