#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits>
#include <iomanip>
#include <thread>
#include <time.h>

#include "utility/Vector3.h"
#include "utility/Ray.h"
#include "utility/Gamma.h"

#include "scene/Camera.h"
#include "scene/Light.h"
#include "scene/SpotLight.h"

#include "hitables/HitRecord.h"
#include "hitables/Hitable.h"
#include "hitables/basic_shapes/Sphere.h"
#include "hitables/World.h"

#include "file_reader/FileUtils.h"
#include "file_reader/Image.h"
#include "file_reader/Reader.h"

#include "shaders/Shader.h"
#include "shaders/BlinnPhongShader.h"
#include "shaders/DefaultShader.h"
#include "shaders/CoolToWarm.h"
#include "shaders/NormalToColor.h"

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
using std::thread;

void ShowRenderingInfo(string fileSpecs, string msg) {
  cout << "\n------- FILE SPECFICATION -------" << endl;
  cout << fileSpecs << endl;
  cout << "---------------------------------" << endl;
  cout << msg << "..." <<flush;
}

void ShowProgress(float num, float denom) {
  float result = num / denom * 100.0;
  string strRes = std::to_string(int(result));
  cout << strRes << "%" << flush;
  cout << string(strRes.length() + 1, '\b') << flush;
}

void PrintExecutionTime(float time) {
  int min = int(time / CLOCKS_PER_SEC) / 60;
  int sec = int(time / CLOCKS_PER_SEC) - (min * 60);
  cout << "\n------------ TIME ---------------" << endl;
  cout << "Rendered file for " << min << "min " << sec << "s" << endl;
  cout << "---------------------------------" << endl;
}

void RenderLine( int *linha, int width, int height, int row, int aliasSamples,               
                 Camera cam, World world, Shader *shader) {
  int kj = 0;
  for(auto col = 0; col < width; col++) {
    RGB tonality (0, 0, 0);
    for(auto s = 0; s < aliasSamples; s++) {
      float u = float(col + drand48()) / float(width);
      float v = float(row + drand48()) / float(height);
      Ray r = cam.ShootRay(u, v);
      tonality += shader->GetColor(r, world);
    }

    tonality /= aliasSamples;
    tonality = GammaCorrection(tonality, 2.0);

    linha[kj++] = int(255.99 * tonality.R());      
    linha[kj++] = int(255.99 * tonality.G());
    linha[kj++] = int(255.99 * tonality.B());
  } 
}

void Render(Image img, Camera cam, World world, Shader *shader) {
  std::clock_t before, after;
  ShowRenderingInfo(img.Description(), "\nRendering");
  vector<thread> threadPool;

  // Initialize rendering with a thread pool
  before = std::clock();
  for(auto row=img.height-1; row>=0; row--) {
    threadPool.push_back(thread (RenderLine, std::ref(img.content[row]), 
             img.width, img.height, row, img.aliasSamples, cam, world, shader));
  }

  // Wait for threads to finish
  for(auto th = 0; th < threadPool.size(); th++){
    threadPool[th].join();
  }
  after = std::clock();
  
  cout << "Done!" << endl;
  PrintExecutionTime(float(after) - float(before));
}

int main( int argc, char *argv[] ) {

  if(argc < 2) {
    cout << "[ERROR] No input file was given!" << endl;
    return 1;
  } else {
    vector<string> input;

    //==== Checks if the file reading was sccessfull
    if(!ReadFile(argv[1], input)){
      //==== Checks if the content in the input file is correct
      Image img;
      if(img.FromContent(input)) {
        //==== Create the Materials
        Material *mat1 = new BlinnPhong(RGB(0.0, 0.0, 1.0), RGB(1.0, 1.0, 1.0),
                                        Vector3(0.5, 0.4, 0.1));

        Material *mat2 = new BlinnPhong(RGB(0.0, 1.0, 0.0), RGB(1.0, 1.0, 1.0), 
                                        Vector3(0.5, 1.0, 0.1));

        Material *mat3 = new BlinnPhong(RGB(1.0, 0.0, 1.0), RGB(1.0, 1.0, 1.0),
                                        Vector3(1.8, 1.0, 0.1));

        Material *mat4 = new BlinnPhong(RGB(0.5, 0.5, 0.5), RGB(1.0, 0.0, 1.0),
                                        Vector3(0.5, 1.0, 0.1));

        Material *mat5 = new BlinnPhong(RGB(1.0, 0.0, 0.0), RGB(1.0, 1.0, 1.0),
                                        Vector3(1.8, 1.0, 0.1));

        //==== Create the Camera
        Camera cam = Camera();
        Camera cam2 = Camera( Point3(-2,2,1), Point3(0,0,-1), Vector3(0,1,0), 90, 
                              float(img.width)/float(img.height));
        
        //==== Create the hitable objects
        std::vector<Hitable*> myHitables = {
          new Sphere(Point3(0, 0, -2), 0.5, mat1),
          // new Sphere(Point3(-1, 0, -2), 0.5, mat2),
          // new Sphere(Point3(1, 0, -2), 0.5, mat3),
          // new Sphere(Point3(0, 1, -2), 0.5, mat5),
          new Sphere(Point3(0, -100.5, -3), 100, mat4)};
        
        //==== Create the world lights
        std::vector<Light*> lights = {
          // new Light(Point3(0, 2, -1), 10.0)
          new SpotLight(Point3(0,2,-2), Vector3(0,-1,0), 10, 1, 20),
          new SpotLight(Point3(2,2,-2), Vector3(-1,-1,0), 10, 1, 30)
        };

        //==== Create the Shader
        Shader *shader = new BlinnPhongShader(100.0);
        World world (myHitables,lights, 0.00001f, 
          std::numeric_limits<float>::max());
        Render(img, cam, world, shader);

        //==== Write the reult into a file
        WriteOnFile(img);
        
        // Unlocking memory
        delete shader;
        delete mat1;
        delete mat2;
        delete mat3;
        delete mat4;
        delete mat5;
      }
    }    
    return 0;
  }
}
