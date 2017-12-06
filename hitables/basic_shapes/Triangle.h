#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_

#include "../Hitable.h"
#include "../../shading_models/materials/Material.h"
#include "../../utility/Angles.h"

#define EPSILON 0.000001

class Triangle : public Hitable {
	public:
		Triangle();
		Triangle(Point3 v1, Point3 v2, Point3 v3, Material *mat);

		bool Hit(Ray r_, HitRecord &rec, float minHit, float maxHit) override;
		Hitable* Translate(Vector3 target) override;
		Hitable* Rotate(Vector3 angles) override;
		Hitable* Scale(Vector3 proportions) override;

		Point3 vert1() const { return vert1_; }
		void set_vert1(Point3 value) { vert1_ = value; }
		Point3 vert2() const { return vert2_; }
		void set_vert2(Point3 value) { vert2_ = value; }
		Point3 vert3() const { return vert3_; }
		void set_vert3(Point3 value) { vert3_ = value; }
		Vector3 edge1() const { return edge1_; }
		Vector3 edge2() const { return edge2_; }

	private:
		Point3 Baricenter();
		Vector3 TranslateVerticle(Vector3 verticle, Vector3 target);
		Vector3 RotateVerticle(Vector3 verticle, Vector3 target);
		Point3 vert1_;
		Point3 vert2_;
		Point3 vert3_;
		Vector3 edge1_;
		Vector3 edge2_;
};

#include "Triangle.inl"

#endif // _TRIANGLE_H_