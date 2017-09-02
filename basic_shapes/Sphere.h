#include <iostream>

#include "../utils/Vec3.h"
#include "../utils/Ray.h"
#include "../scene/Actor.h"

class Sphere : public Actor 
{
public:
	// The sphere radius length
	double radius;

	/* Constructs a new Sphere with center at origin and diameter
		 of 2 radius */ 
	Sphere (Point3 origin, double radius) 
	{
		this->origin = origin;
		this->radius = radius;
	}

	inline bool hit (const Ray & ray) override 
	{
		Vec3 oc = ray.get_origin() - origin;
    float A = dot(ray.get_direction(), ray.get_direction());
    float B = 2.0 * dot(oc, ray.get_direction());
    float C = dot(oc, oc) - (radius * radius);

    float delta = (B * B) - 4 * A * C;
    return delta > 0;
	}

	inline Vec3 hitPoint (const Ray & ray, bool lowerRoot=false) override 
	{
		double A, B, C;
		double delta = hit(ray, A, B, C);
		Vec3 normal;
		if(delta > 0){
			float t1 = (-B - sqrt(delta)) / (2.0 * A);
      float t2 = (-B + sqrt(delta)) / (2.0 * A);
      float root = (lowerRoot) ? (t1) : (t2);
      normal = ray.point_at(root);
		}
		return normal;
	}

private:	

	/* This method does the same of public hit function, but receives
	   three references to sotre the result of delta parameters.

	   @param r_ The ray being shooted at the image.
	   @param A The A from Baskhara formula.
	   @param B The B from Baskhara formula.
	   @param C The C from Baskhara formula.
	   @return double The value of Delta.*/
	inline double hit(const Ray & ray, double &A, double &B, double &C) 
	{
		Vec3 oc = ray.get_origin() - origin;
    A = dot(ray.get_direction(), ray.get_direction());
    B = 2.0 * dot(oc, ray.get_direction());
    C = dot(oc, oc) - (radius * radius);
    float delta = (B * B) - 4 * A * C;
    return delta;
	}
};
