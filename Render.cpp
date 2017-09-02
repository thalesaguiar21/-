#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "utils/Vec3.h"
#include "utils/Ray.h"
#include "utils/Image.h"
#include "utils/FileReader.h"

#include "scene/Camera.h"
#include "scene/Scene.h"

#include "basic_shapes/Sphere.h"

#include "shaders/Shader.h"
#include "shaders/NormalToColor.h"

using namespace utility;
using std::string;
using std::vector;

/*
 *  In the near future we'll want to refactor our project to become
 *  something like the code below.
 */
#ifdef TRADITIONAL_RT
Image Raytrace (Camera cam, Scene scene, int width, int height)
{
    Image image = new Image (width, height) ;
    for (int i = 0 ; i < height ; i++)
        for (int j = 0 ; j < width ; j++) {
            Ray ray = RayThruPixel (cam, i, j) ;
            Intersection hit = Intersect (ray, scene) ;
            image[i][j] = FindColor (hit) ;
            }
    return image ;
}
#endif

int main( int argc, char *argv[]  )  
{
  std::ofstream myfile;

  if(argc < 2){
    std::cout << "No input file name was given! Closing the program." <<std::endl;
    return 1;
  } else {
    vector<string> content = utility::read_file(argv[1]);
    Image img;
    img.from(content);
    std::ofstream imgFile("imgs/" + img.name);

    imgFile << "P3" << "\n";
    imgFile << img.width << " " << img.height << "\n";
    imgFile << "255\n";

    Camera cam (Point3(-2, -1, -1), Point3(0, 0, 0), Vec3(4, 0, 0), Vec3(0, 2, 0));
    vector<Actor*> actors = { new Sphere(Point3 (-0.35,0,-1.0), 0.4),
                              new Sphere(Point3 (-0.25,0, -3.0), 0.8),
                              new Sphere(Point3 (0.45,0, -2.0), 0.1)};
    Scene scene (cam, actors);
    Shader *shader = new NormalToColor(true);

    // NOTICE: We loop rows from bottom to top.
    for ( auto row = img.height - 1 ; row >= 0 ; --row ) { //Y
      for( auto col = 0 ; col < img.width ; col++ ) { // X 
        Ray r = cam.getRay(col, row, img.width, img.height);

        RGB c = shader->getColor(r, img, scene);

        int ir = int( 255.99f * c[RGB::R] );
        int ig = int( 255.99f * c[RGB::G] );
        int ib = int( 255.99f * c[RGB::B] );

        imgFile << ir << " " << ig << " " << ib << "\n";
      }
    }
    delete shader;
  }


  return 0;
}
