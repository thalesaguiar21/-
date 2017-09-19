#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits>
#include <iomanip>

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

Vector3 RandomInUnitSphere() {
  Vector3 p;
  do {
    p = 2.0 * Vector3(drand48(), drand48(), drand48()) - Vector3(1.0, 1.0, 1.0);
  } while(dot(p, p) >= 1.0);
  return p;
}

RGB color2( Ray r_, World world, int reflections ) {
  HitRecord rec;
  if(reflections <= 0){
    return RGB(0, 0, 0);
  }
  if(world.HitAnything(r_, rec)) {
    Vector3 target = rec.hitPoint + rec.normal + RandomInUnitSphere();
    return 0.5 * RGB(0.7, 0.0, 0.0) * color2(Ray(rec.hitPoint, target - rec.hitPoint), world, reflections-1);
  } else {
    Vector3 unitDirection = UnitVector(r_.Direction());
    float t = 0.5 * (unitDirection.Y() + 1.0);
    return (1.0 - t)*RGB(1.0, 1.0, 1.0) + t*RGB(0.5, 0.7, 1.0);
  }
}

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

void ShowRenderingInfo(string fileSpecs, string msg) {
  cout << "FILE SPECFICATION:" << endl;
  cout << "-----------------------------" << endl;
  cout << fileSpecs << endl;
  cout << "-----------------------------" << endl;
  cout << msg << " >>> " << flush;
}

void ShowProgress(float num, float denom) {
  float result = num / denom * 100.0;
  string strRes = std::to_string(int(result));
  cout << strRes << "%" << flush;
  cout << string(strRes.length() + 1, '\b') << flush;
}

void Render(Image &img, Camera cam, World world) {
  ShowRenderingInfo(img.Description(), "Rendering");
  for(auto row=img.height-1; row>=0; row--) {
    for(auto col=0; col<img.width; col++) {
      RGB tonality (0, 0, 0);
      for(auto s=0; s<img.aliasSamples; s++) {
        float u = float(col + drand48()) / float(img.width);
        float v = float(row + drand48()) / float(img.height);
        Ray r = cam.ShootRay(u, v);
        tonality += color2(r, world, 5);
        //tonality += color(r, world);
      }
      tonality /= img.aliasSamples;
      tonality = RGB( sqrt(tonality.R()), sqrt(tonality.G()), sqrt(tonality.B()));

      int ir = int(255.99 * tonality.R());
      int ig = int(255.99 * tonality.G());
      int ib = int(255.99 * tonality.B());

      img.buff += std::to_string(ir) + " " +
                  std::to_string(ig) + " " +
                  std::to_string(ib) + "\n";
    }
    ShowProgress(img.height - row, img.height);
  }
  cout << endl;
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
    std::vector<Hitable*> myHitables = {  new Sphere(Point3(0, 0, -1.0), 0.5),
                                          new Sphere(Point3(0, -100.5, -1), 100)};
    World world (myHitables, 0.0, std::numeric_limits<float>::max());
    Render(img, cam, world);

    std::ofstream file("../" + img.name);
    file << img.Header();
    file << img.buff;
    file.close();
    return 0;
  }
}
