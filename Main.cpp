#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits>

#include "utility/Vector3.h"
#include "utility/Ray.h"
#include "scene/Camera.h"
#include "hitables/HitRecord.h"
#include "hitables/Hitable.h"
#include "hitables/basic_shapes/Sphere.h"
#include "hitables/World.h"
#include "file_reader/Image.h"
#include "file_reader/Reader.h"

using namespace utils;
using namespace hitables;
using namespace filerd;

using basicShapes::Sphere;
using std::cout;
using std::endl;
using std::string;
using std::flush;
using std::vector;

RGB color( Ray r_, World world ) {
  HitRecord rec;
  RGB tonality (0, 0, 0);
  if(world.HitAnything(r_, rec)) {
    tonality =  0.5 * (Vector3(1.0, 1.0, 1.0) + UnitVector(rec.normal));
  } else {
    Vector3 unitDirection = UnitVector(r_.Direction());
    float t = 0.5 * (unitDirection.Y() + 1.0);
    tonality = (1.0 - t)*RGB(1.0, 1.0, 1.0) + t*RGB(0.5, 0.7, 1.0);
  }
  return tonality;
}

int main( int argc, char *argv[] ) {

  if(argc < 2) {
    cout << "[ERROR] No input file was given!" << endl;
    return 1;
  } else {
    vector<string> input = ReadFile(argv[1]);
    Image img;
    img.FromContent(input);
    Camera cam (Point3(0,0,0), Point3(-2, -1, -1), Vector3(4, 0, 0), Vector3(0, 2, 0));
    std::vector<Hitable*> myHitables = {  new Sphere(Point3(0, 0, -1.0), 0.3),
                                          new Sphere(Point3(0, -100.5, -1), 100)};
    World world (myHitables, 0.0, std::numeric_limits<float>::max());

    for(auto row=img.height-1; row>=0; row--) {
      for(auto col=0; col<img.width; col++) {
        float u = float(col) / float(img.width);
        float v = float(row) / float(img.height);
        Ray r = cam.ShootRay(u, v);
        RGB tonality = color(r, world);

        int ir = int(255.99 * tonality.R());
        int ig = int(255.99 * tonality.G());
        int ib = int(255.99 * tonality.B());

        img.buff += std::to_string(ir) + " " +
                    std::to_string(ig) + " " +
                    std::to_string(ib) + "\n";
      }
    }
    std::ofstream file("../" + img.name);
    file << img.Header();
    file << img.buff;
    file.close();
    return 0;
  }
}
