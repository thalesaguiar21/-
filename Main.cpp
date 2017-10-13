#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits>
#include <iomanip>

#include "utility/Vector3.h"
#include "utility/Ray.h"
#include "utility/Gamma.h"

#include "scene/Camera.h"
#include "scene/Light.h"

#include "hitables/HitRecord.h"
#include "hitables/Hitable.h"
#include "hitables/basic_shapes/Sphere.h"
#include "hitables/World.h"

#include "file_reader/Image.h"
#include "file_reader/Reader.h"

#include "shaders/Shader.h"
#include "shaders/BlinnPhongShader.h"
#include "shaders/DefaultShader.h"

#include "materials/Material.h"
#include "materials/Lambertian.h"
#include "materials/Metalic.h"
#include "materials/BlinnPhong.h"

using namespace utils;
using namespace filerd;

using std::cout;
using std::endl;
using std::string;
using std::flush;
using std::vector;

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

void Render(Image &img, Camera cam, World world, Shader *shader) {
  ShowRenderingInfo(img.Description(), "Rendering");
  for(auto row=img.height-1; row>=0; row--) {
    for(auto col=0; col<img.width; col++) {
      RGB tonality (0, 0, 0);
      for(auto s=0; s<img.aliasSamples; s++) {
        float u = float(col + drand48()) / float(img.width);
        float v = float(row + drand48()) / float(img.height);
        Ray r = cam.ShootRay(u, v);
        tonality += shader->GetColor(r, world);
      }
      tonality /= img.aliasSamples;
      tonality = GammaCorrection(tonality, 2.0);

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
    Camera cam2 (Vector3(0,0,0), Vector3(0,0,-1), Vector3(0,1,0), 90, float(img.width)/float(img.height));

    Light *light1 = new Light();
    light1->Origin = Vector3(0, 0, -2.0);

    Light *light2 = new Light();
    light2->Origin = Vector3(50, 100, 0);

    std::vector<Light*> lights = { light1 };

    Material *mat1 = new Lambertian(RGB(1.0, 0.0, 0.0), 0.5);
    Material *mat3 = new Lambertian(RGB(0.0, 1.0, 0.0), 0.5);
    Material *mat4 = new Lambertian(RGB(0.0, 0.0, 1.0), 0.5);
    Material *mat5 = new BlinnPhong(RGB(0.0, 0.0, 1.0), RGB(1.0, 1.0, 1.0), Vector3(1.8, 1.0, 0.1));

    Material *mat2 = new BlinnPhong(RGB(0.5, 0.5, 0.5), RGB(1.0, 0.0, 1.0), Vector3(0.5, 1.0, 0.1));


    // Material *mat1 = new Lambertian(RGB(1.0, 0, 0), 0.5);
    // Material *mat2 = new Lambertian(RGB(0.8, 0.8, 0), 0.5);
    // Material *mat3 = new Metalic(RGB(0, 0.6, 0.6), 0.5);
    // Material *mat4 = new Metalic(RGB(0.8, 0.8, 0.8), 0.5);
    float R = cos(3.14159/4);
    std::vector<Hitable*> myHitables = {
      new Sphere(Point3(-R, 0, -1), R, mat1),
      new Sphere(Point3(R, 0, -1), R, mat3),
      // new Sphere(Point3(-1, 0, -2), 0.5, mat4),
      // new Sphere(Point3(0, 1, -2), 0.5, mat5),
      new Sphere(Point3(0, -100.5, -2), 100, mat4)
    };

    World world (myHitables, 0.0, std::numeric_limits<float>::max());
    world.lights = lights;
    Shader *shader = new DefaultShader(5);
    Render(img, cam2, world, shader);

    std::ofstream file("../" + img.name);
    file << img.Header();
    file << img.buff;
    file.close();

    delete shader;
    delete mat1;
    delete mat2;
    delete mat3;
    delete mat4;
    delete mat5;
    delete light1;
    delete light2;
    return 0;
  }
}
