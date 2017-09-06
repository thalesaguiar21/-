#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "../utils/Vec3.h"

class Camera {
public:
    // lower left corner of the view plane
    Point3 llc;
    // the camera's origin.
    Point3 origin;
    // Horizontal dimension of the view plane.
    Vec3 horizontal;
    // Vertical dimension of the view plane.
    Vec3 vertical;

    /* The default constructor will create a Camera with llc and origin at (0,0,0)
    and horizontal and vertical with direction (0,0,0).*/
    Camera ()
    {
        llc = Point3(0, 0, 0);
        origin = Point3(0, 0, 0);
        horizontal = Vec3(0 , 0, 0);
        vertical = Vec3(0, 0, 0);
    }

    Camera (Point3 lowerLeftCorner, Point3 origin, Vec3 horizontal, Vec3 vertical)
    {
        llc = lowerLeftCorner;
        this->origin = origin;
        this->horizontal = horizontal;
        this->vertical = vertical;
    }

    /* Given the image dimension and a position, returns a Ray
    that is hitting this point in the image.

    @param col The x-axis coordinate
    @param row The y-axis coordinate
    @param width The image width
    @param height The image height
    @return A Ray object that hits the specified point
    */
    inline Ray getRay(int col, int row, int width, int height)
    {
        auto u = float(col) / float(width - 1);
        auto v = float(row) / float(height - 1);
        return makeRay(u, v);
    }

    /* Given the image dimension and a position, returns a Ray
    from camera's origin to a point in the image. Note that
    this method returns a ray with a random component, that
    is, it is used for anti aliasing.

    @param col The x-axis coordinate
    @param row The y-axis coordinate
    @param width The image width
    @param height The image height
    @return A Ray object that hits the specified point
    */
    inline Ray getRayAntiAliasing(int col, int row, int width, int height)
    {
        auto u = float(col + drand48()) / float(width - 1);
        auto v = float(row + drand48()) / float(height - 1);
        return makeRay(u, v);
    }

private:

    /* Given two vector's length, make the tranformation
       from the camera to the view plane and create a Ray.

       @param u The horizontal length
       @param v The vertical length
    */
    inline Ray makeRay(double u, double v)
    {
        Point3 end_point = llc + u*horizontal + v*vertical ;
        return Ray( origin, end_point - origin );
    }

};

#endif
