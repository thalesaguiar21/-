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

#include "scene/lights/Light.h"
#include "scene/lights/SpotLight.h"
#include "scene/lights/AreaLight.h"
#include "scene/cameras/Camera.h"
#include "scene/cameras/ParallelCamera.h"
#include "scene/cameras/PerspectiveCamera.h"

#include "shading_models/materials/Material.h"
#include "shading_models/materials/Lambertian.h"
#include "shading_models/materials/Metalic.h"
#include "shading_models/materials/BlinnPhong.h"

#include "hitables/HitRecord.h"
#include "hitables/Hitable.h"
#include "hitables/basic_shapes/Sphere.h"
#include "hitables/basic_shapes/Triangle.h"
#include "hitables/basic_shapes/Cube.h"
#include "hitables/World.h"

#include "file_reader/FileUtils.h"
#include "file_reader/Image.h"
#include "file_reader/Reader.h"

#include "Renderer.h"
// vec3, vec4, ivec4, mat4
#include "external/glm/glm.hpp"
// translate, rotate, scale, perspective
#include "external/glm/gtc/matrix_transform.hpp"

using std::cout;
using std::endl;
using std::string;
using std::numeric_limits;

using namespace utils;
using namespace filerd;

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
        Material *blinnPhong1 = new BlinnPhong(RGB(0.0, 0.0, 1.0), RGB(1.0, 1.0, 1.0), 0.01f, 0.8f, 0.2f, 30);
        Material *blinnPhong2 = new BlinnPhong(RGB(0.8, 0.8, 0.0), RGB(1.0, 1.0, 1.0), 0.01f, 0.8f, 0.2f, 30);
        // Material *mat2 = new BlinnPhong(RGB(0.0, 1.0, 0.0), RGB(1.0, 1.0, 1.0), 0.001f, 0.7f, 0.3f);
        // Material *mat4 = new BlinnPhong(RGB(0.5, 0.5, 0.5), RGB(1.0, 1.0, 1.0), 0.01f, 0.9f, 0.1f);
        Material *lambertian1 = new Lambertian(RGB(1.0, 0.0, 0.0), 0.5, 10);
        Material *lambertian2 = new Lambertian(RGB(0.5, 0.5, 0.5), 0.5, 10);
        Material *lambertian3 = new Lambertian(RGB(0.8, 0.8, 0.0), 0.5, 10);
        Material *metalic = new Metalic(RGB(0.8, 0.6, 0.4), 0.3, 10);

        //==== Create the Camera
        // Perspective Camera
        float dist = (Point3(0,3,2) - Point3(0,0,-2)).Length();
        Camera *perspecCam = new PerspectiveCamera( Point3(-0.5,1,1), Point3(0,0,0), 120, 
                              float(img.width)/float(img.height), 0, 5);

        // Parallel Camera
        Camera *orthoCam = new ParallelCamera( Point3(0,1,2), Point3(0,0,-1),
                                           -4, 4, -2, 2);
        
        //==== Create the hitable objects

        Sphere *original = new Sphere(Point3(0,0,-1), 0.5, lambertian1);
        Sphere *sphere2 = new Sphere(Point3(1,0,-1), 0.5, blinnPhong1);
        Sphere *metalSphere = new Sphere(Point3(-1,0,-1), 0.5, metalic);

        std::vector<Hitable*> myHitables = {
          original,
          // sphere2,
          metalSphere,
          new Sphere(Point3(0, -100.5, -3), 100, lambertian3)
        };
        
        //==== Create the world lights
        std::vector<Light*> lights = {
          new Light(Point3(0, 3, 1), 10.0)
          // new SpotLight(Point3(2,2,-3), Vector3(-1,-1,0), 10, 1, 45)
          // new SpotLight(Point3(0,2,-2), Vector3(0,-1,0), 10, 1, 60)
        };

        //==== Create the Shader
        World world (myHitables, lights, 0.0001f, numeric_limits<float>::max());
        Renderer renderer = Renderer(img, orthoCam, world);
        renderer.Start();

        //==== Write the result into a file
        WriteOnFile(img);
        
        // Unlocking memory
        delete orthoCam;
        delete perspecCam;
        delete blinnPhong1;
        delete blinnPhong2;
        delete lambertian1;
        delete lambertian2;
        delete lambertian3;
        // delete mat4;
        // delete mat2;
        delete metalic;
        delete original;
        delete sphere2;
        delete metalSphere;
      }
    }    
    return 0;
  }
}
