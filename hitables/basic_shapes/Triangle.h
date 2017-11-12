#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_

#include "../Hitable.h"
#include "../../materials/Material.h"


#define EPSILON 0.00001

class Triangle : public Hitable {
	public:
		Triangle();
		Triangle(Point3 v1, Point3 v2, Point3 v3, Material *mat);

		bool Hit(Ray r_, HitRecord &rec, float minHit, float maxHit) override;

		Point3 vert1() const { return vert1_; };
		void set_vert1(Point3 value) { vert1_ = value; };
		Point3 vert2() const { return vert2_; };
		void set_vert2(Point3 value) { vert2_ = value; };
		Point3 vert3() const { return vert3_; };
		void set_vert3(Point3 value) { vert3_ = value; };

	private:
		Point3 vert1_;
		Point3 vert2_;
		Point3 vert3_;
};

#include "Triangle.inl"

#endif // _TRIANGLE_H_