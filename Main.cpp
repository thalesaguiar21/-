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
        //==== Create the Materials
        // Texture *imgTexture = new ImageTexture();
        int nx, ny, nn;
        unsigned char *tex_data = stbi_load("voyager.jpg", &nx, &ny, &nn, 0);
        std::cout << "HEY" << std::endl;
        Texture *imgTexture = new ImageTexture(tex_data, nx, ny);
        Texture *checker = new CheckerTexture(new ConstantTexture(RGB(0.2, 0.3, 0.1)), 
                                              new ConstantTexture(RGB(0.9, 0.9, 0.9)));
        Texture *perlin = new PerlinTexture(1.0);
        Material *mat1 = new BlinnPhong(RGB(0, 0.0, 1.0), RGB(1.0, 1.0, 1.0),
                                        Vector3(0.01, 0.8, 0.2));
        Material *mat2 = new BlinnPhong(RGB(0.0, 1.0, 0.0), RGB(1.0, 1.0, 1.0), 
                                        Vector3(0.001, 0.7, 0.3));
        Material *mat4 = new BlinnPhong(RGB(0.5, 0.5, 0.5), RGB(1.0, 1.0, 1.0),
                                        Vector3(0.01, 0.9, 0.1));
        Material *lambertian = new Lambertian(checker, 0.5);
        Material *lambertian2 = new Lambertian(perlin, 0.5);
        Material *metalic = new Metalic(new ConstantTexture(RGB(0.8, 0.6, 0.2)), 0.3);
        Material *dielectric = new Dielectric(1.5f);
        Material *voyager = new Lambertian(imgTexture, 0.5);

        //==== Create the Camera
        // Perspective Camera
        float dist = (Point3(0,3,2) - Point3(0,0,-2)).Length();
        Camera *perspecCam = new PerspectiveCamera( Point3(0,0,0), Point3(0,0,-1), 120, 
                              float(img.width)/float(img.height), 0, 5);

        // Parallel Camera
        Camera *orthoCam = new ParallelCamera( Point3(0,2,2), Point3(0,0,-1),
                                           -8, 8, -4, 4);
        
        //==== Create the hitable objects
        Point3 center (0, 0, -1);
        glm::vec4 p1(0, 2, 0, 1);

        Point3 v1 (-1.5, 1, 0);
        Point3 v2 (1.5, 1, 0);
        Point3 v3 (1, 1, 2);

        Sphere *original = new Sphere(center, 0.5, mat1);
        Sphere *metalicSphere = new Sphere(Point3(2,1,-1), 1.5, mat2);
        Sphere *glassSphere = new Sphere(Point3(-1,2,-2), 2, voyager);
        Sphere *littleGlassSphere = new Sphere(Point3(-1,0,-1), -0.45, dielectric);
        Triangle *orig_triang = new Triangle(v1, v2, v3, mat1);
        Hitable *cube = new Cube(-1,5,1,4,-2,-3, mat1);

        std::vector<Hitable*> myHitables = {
          original,
          metalicSphere,
          // glassSphere,
          // littleGlassSphere,
          new Sphere(Point3(0, -100.5, -3), 100, mat4)
          };
        
        //==== Create the world lights
        std::vector<Light*> lights = {
          new Light(Point3(0, 3, 1), 10.0)
          // new SpotLight(Point3(2,2,-3), Vector3(-1,-1,0), 10, 1, 45)
          // new SpotLight(Point3(0,2,-2), Vector3(0,-1,0), 10, 1, 60)
        };

        //==== Create the Shader
        Shader *shader = ShaderFactory::Create(ShaderType::blinnPhong, 30.0);
        World world (myHitables,lights, 0.01f, numeric_limits<float>::max());
        Renderer renderer = Renderer(img, orthoCam, world, shader);
        renderer.Start();

        //==== Write the result into a file
        WriteOnFile(img);
        
        // Unlocking memory
        delete shader;
        delete orthoCam;
        delete perspecCam;
        delete mat1;
        delete mat2;
        delete lambertian;
        delete lambertian2;
        delete mat4;
        delete metalic;
        delete original;
        delete orig_triang;
        delete dielectric;
        delete glassSphere;
        delete littleGlassSphere;
        delete perlin;
        delete checker;
      }
    }    
    return 0;
  }
}
