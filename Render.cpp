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




RGB backgroundColor(const Ray & r_, Image img)
{
    // If no Actor was hit, then hits the background.
    auto unit = utility::unit_vector( r_.get_direction() );
    auto tx = (unit.x() + 1.0) / 2.0;
    auto ty = (unit.y() + 1.0) / 2.0;

    RGB upper = (1 - tx) * img.upper_left + tx * img.upper_right;
    RGB lower = (1 - tx) * img.lower_left + tx * img.lower_right;
    return (1 - ty) * lower + ty * upper;
}

void renderWithAntiAliasing(string fileName, Scene scene, Image img, Camera cam, Shader *shader, int samples)
{
    std::cout << "Rendering file '" << fileName << "'..." << std::flush;
    std::ofstream file(fileName);

    file << "P3" << "\n";
    file << img.width << " " << img.height << "\n";
    file << "255\n";

    Ray camRay (Point3 (0.0, 0.0, 0.0), Vec3 (0.0, 0.0, 0.0));
    RGB color (0.0, 0.0, 0.0);
    bool hitActor = false;

    // NOTICE: We loop rows from bottom to top.
    for ( auto row = img.height - 1 ; row >= 0 ; --row ) { //Y
        for( auto col = 0 ; col < img.width ; col++ ) { // X
            color  = RGB (0.0, 0.0, 0.0);
            hitActor = false;
            for(int act=0; act < scene.actors.size(); act++) {
                camRay = cam.getRay(col, row, img.width, img.height);
                if( scene.actors[act]->hit(camRay)) {
                    hitActor = true;
                    for(int s=0; s < samples; s++ ){
                        camRay = cam.getRayAntiAliasing(col, row, img.width, img.height);
                        color += scene.actors[act]->getColor(camRay);
                    }
                    color /= float(samples);
                    break;
                }
            }

            if (!hitActor) {
                color = backgroundColor(camRay, img);
            }

            int ir = int( 255.99f * color[RGB::R] );
            int ig = int( 255.99f * color[RGB::G] );
            int ib = int( 255.99f * color[RGB::B] );

            file << ir << " " << ig << " " << ib << "\n";
        }
    }
    file.close();
    std::cout << "Done!" << std::endl;
}


/*void renderize(string fileName, Scene scene, Image img, Camera cam, Shader *shader)
{
std::cout << "Rendering file '" << fileName << "'...";
std::ofstream file(fileName);

file << "P3" << "\n";
file << img.width << " " << img.height << "\n";
file << "255\n";

RGB color (0, 0, 0);
// NOTICE: We loop rows from bottom to top.
for ( auto row = img.height - 1 ; row >= 0 ; --row ) { //Y
for( auto col = 0 ; col < img.width ; col++ ) { // X
Ray r = cam.getRay(col, row, img.width, img.height);
color = shader->getColor(r, img, scene);

int ir = int( 255.99f * color[RGB::R] );
int ig = int( 255.99f * color[RGB::G] );
int ib = int( 255.99f * color[RGB::B] );

file << ir << " " << ig << " " << ib << "\n";
}
}
file.close();
std::cout << "Done!" << std::endl;
}*/

int main( int argc, char *argv[]  )
{
    if(argc < 2){
        std::cout << "No input file name was given! Closing the program." <<std::endl;
        return 1;
    } else {
        vector<string> content = utility::read_file(argv[1]);
        Image img;
        img.from(content);

        Shader *shader = new NormalToColor(true);
        Camera cam (Point3(-2, -1, -1), Point3(0, 0, 0), Vec3(4, 0, 0), Vec3(0, 2, 0));
        vector<Actor*> actors = { new Sphere(shader, Point3 (0.45,0, -1.0), 0.4) };
        Scene scene (cam, actors);

        renderWithAntiAliasing("imgs/" + img.name, scene, img, cam, shader, 500);
        //renderize("imgs/" + img.name, scene, img, cam, shader);
        delete shader;
    }

    return 0;
}
