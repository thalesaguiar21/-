#include <iostream>
#include <fstream>
#include "utils/vec3.h"
#include "utils/ray.h"

using namespace utility;

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

bool hit_sphere(const point3 & center, float radius, const Ray & ray){

    vec3 oc = ray.get_origin() - center;
    float A = dot(ray.get_direction(), ray.get_direction());
    float B = 2.0 * dot(oc, ray.get_direction());
    float C = dot(oc, oc) - (radius * radius);

    float delta = (B * B) - 4 * A * C;
    //float t1 = (-B + sqrt(delta)) / (2 * A);
    //float t2 = (-B - sqrt(delta)) / (2 * A);

    return delta > 0;
}


rgb color( const Ray & r_ )
{
    rgb top    (0, 0.5, 1);
    rgb bottom (1, 1, 1);

    auto unit = utility::unit_vector( r_.get_direction() );
    auto unit_y = unit.y();

    // TODO: determine the background color, which is an linear interpolation between bottom->top.
    // The interpolation is based on where the ray hits the background.
    // Imagine that the background is attached to the view-plane; in other words,
    // the virtual world we want to visualize is empty!

    auto t = (unit_y + 1) / 2;
    rgb result = bottom + t * (top - bottom);
    return result; // Stub, replace it accordingly
}

int main( int argc, char *argv[]  )
{
    std::ofstream myfile;

    if(argc < 2){
        std::cout << "No input file name was given! Closing the program." <<std::endl;
        return 1;
    } else {
        myfile.open(argv[1]);
        int n_cols{ 1136 };
        int n_rows{ 640 };

        myfile    << "P3\n"
                  << n_cols << " " << n_rows << "\n"
                  << "255\n";

        //=== Defining our 'camera'
        point3 lower_left_corner( -2, -1, -1 ); // lower left corner of the view plane.
        vec3 horizontal( 4, 0, 0 ); // Horizontal dimension of the view plane.
        vec3 vertical(0, 2, 0); // Vertical dimension of the view plane.
        point3 origin(0, 0, 0); // the camera's origin.

         // NOTICE: We loop rows from bottom to top.
        for ( auto row{n_rows-1} ; row >= 0 ; --row ) // Y
        {
            for( auto col{0} ; col < n_cols ; col++ ) // X
            {
                // Determine how much we have 'walked' on the image: in [0,1]
                auto u = float(col) / float( n_cols ); // walked u% of the horizontal dimension of the view plane.
                auto v = float(row) / float( n_rows ); // walked v% of the vertical dimension of the view plane.

                // Determine the ray's direction, based on the pixel coordinate (col,row).
                // We are mapping (matching) the view plane (vp) to the image.
                // To create a ray we need: (a) an origin, and (b) an end point.
                //
                // (a) The ray's origin is the origin of the camera frame (which is the same as the world's frame).
                //
                // (b) To get the end point of ray we just have to 'walk' from the
                // vp's origin + horizontal displacement (proportional to 'col') +
                // vertical displacement (proportional to 'row').
                point3 end_point = lower_left_corner + u*horizontal + v*vertical ;
                // The ray:
                Ray r( origin, end_point - origin );
                point3 center (0, 0, 1);
                float radius = 0.2;
                rgb c;

                if(hit_sphere(center, radius, r)){
                    c = rgb (1, 0, 0);
                } else {
                    // Determine the color of the ray, as it travels through the virtual space.
                    c = color( r );
                }

                int ir = int( 255.99f * c[rgb::R] );
                int ig = int( 255.99f * c[rgb::G] );
                int ib = int( 255.99f * c[rgb::B] );

                myfile << ir << " " << ig << " " << ib << "\n";
            }
        }

        myfile.close();
    }

    return 0;
}
