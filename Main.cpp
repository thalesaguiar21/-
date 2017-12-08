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
#include "utility/Perlin.h"

#include "scene/lights/Light.h"
#include "scene/lights/SpotLight.h"
#include "scene/lights/AreaLight.h"
#include "scene/cameras/Camera.h"
#include "scene/cameras/ParallelCamera.h"
#include "scene/cameras/PerspectiveCamera.h"

#include "materials/Material.h"
#include "materials/Lambertian.h"
#include "materials/Metalic.h"
#include "materials/Dielectric.h"
#include "materials/BlinnPhong.h"
#include "materials/textures/Texture.h"
#include "materials/textures/ConstantTexture.h"
#include "materials/textures/CheckerTexture.h"
#include "materials/textures/PerlinTexture.h"
#include "materials/textures/ImageTexture.h"

#include "hitables/HitRecord.h"
#include "hitables/Hitable.h"
#include "hitables/Transformer.h"
#include "hitables/basic_shapes/Sphere.h"
#include "hitables/basic_shapes/Triangle.h"
#include "hitables/basic_shapes/Cube.h"
#include "hitables/World.h"

#include "file_reader/FileUtils.h"
#include "file_reader/Image.h"
#include "file_reader/Reader.h"

#include "shaders/factory/ShaderFactory.h"
#include "shaders/factory/ShaderType.h"

#include "Renderer.h"
// vec3, vec4, ivec4, mat4
#include "external/glm/glm.hpp"
// translate, rotate, scale, perspective
#include "external/glm/gtc/matrix_transform.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "external/stb_image.h"

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
        //==== Create the Textures
        int nx, ny, nn;
        unsigned char *tex_data = stbi_load("bricks.jpg", &nx, &ny, &nn, 0);
        Texture *imgTexture = new ImageTexture(tex_data, nx, ny);
        Texture *greenTexture = new ConstantTexture(RGB(0.2, 0.3, 0.1));
        Texture *greyTexture = new ConstantTexture(RGB(0.9, 0.9, 0.9));
        Texture *coble = new ConstantTexture(RGB(0.8, 0.6, 0.2));
        Texture *checker = new CheckerTexture(greenTexture, greyTexture);
        Texture *perlin = new PerlinTexture(1.0);

        //==== Create the BlinnPhong materials
        Material *mat1 = new BlinnPhong(RGB(0, 0.0, 1.0), RGB(1.0, 1.0, 1.0),
                                        Vector3(0.01, 0.8, 0.2));
        Material *mat2 = new BlinnPhong(RGB(0.0, 1.0, 0.0), RGB(1.0, 1.0, 1.0), 
                                        Vector3(0.001, 0.7, 0.3));
        Material *mat4 = new BlinnPhong(RGB(0.5, 0.5, 0.5), RGB(1.0, 1.0, 1.0),
                                        Vector3(0.01, 0.9, 0.1));
        //==== Create the materials
        Material *greenMat = new Lambertian(greenTexture, 0.5);
        Material *greyMat = new Lambertian(greyTexture, 0.5);
        Material *perlinMat = new Lambertian(perlin, 0.5);
        Material *metal = new Metalic(coble, 0.3);
        Material *dielectric = new Dielectric(1.05f);
        Material *chekerMat = new Lambertian(checker, 0.5);
        Material *imgMat = new Lambertian(imgTexture, 0.5);

        //==== Create the hitable objects
        Point3 v1 (-1.5, 1, 0);
        Point3 v2 (1.5, 1, 0);
        Point3 v3 (1, 1, 2);

        Sphere *constSphere = new Sphere(Point3(0,0,-1), 0.5, greenMat);
        Sphere *imgSphere = new Sphere(Point3(3,2,-2), 1.5, perlinMat);
        Sphere *glassSphere = new Sphere(Point3(1.5,2,4), 1.5, dielectric);
        Sphere *perlinSphere = new Sphere(Point3(-2,0,-1), 0.5, chekerMat);
        Sphere *metalSphere = new Sphere(Point3(1,0,-1), 0.5, metal);

        //==== Create the Camera
        // Perspective Camera
        Camera *perspecCam = new PerspectiveCamera( Point3(0,0,0), Point3(0,0,-1), 120, 
                              float(img.width)/float(img.height), 0, 5);
        // Parallel Camera
        Camera *orthoCam = new ParallelCamera( Point3(1,10,100), Point3(0,0,-1),
                                           -8, 8, -4, 4);

        std::vector<Hitable*> myHitables = {
          constSphere,
          imgSphere,
          glassSphere,
          perlinSphere,
          metalSphere,
          new Sphere(Point3(0, -100.5, -3), 100, imgMat)
        };
        
        //==== Create the world lights
        std::vector<Light*> lights = {
          new Light(Point3(0, 3, 1), 10.0)
          // new SpotLight(Point3(2,2,-3), Vector3(-1,-1,0), 10, 1, 45)
          // new SpotLight(Point3(0,2,-2), Vector3(0,-1,0), 10, 1, 60)
        };

        //==== Create the Shader
        Shader *shader = ShaderFactory::Create(ShaderType::defaultShader, 50.0);
        World world (myHitables,lights, 0.01f, numeric_limits<float>::max());
        Renderer renderer = Renderer(img, orthoCam, world, shader);
        renderer.Start();

        //==== Write the result into a file
        WriteOnFile(img);
        
        // Unlocking memory
        delete shader;

        delete imgTexture;
        delete greenTexture;
        delete greyTexture;
        delete coble;
        delete checker;
        delete perlin;

        delete greenMat;
        delete greyMat;
        delete metal;
        delete dielectric;
        delete chekerMat;

        delete constSphere;
        delete imgSphere;
        delete glassSphere;
        delete perlinSphere;
        delete metalSphere;
      }
    }    
    return 0;
  }
}
