#include "Triangle.h"

Triangle::Triangle() {
	vert1_ = Point3(0.f);
	vert2_ = Point3(1.f);
	vert3_ = Point3(-1.f);
}

Triangle::Triangle(Point3 v1, Point3 v2, Point3 v3, Material *mat) {
	vert1_ = v1;
	vert2_ = v2;
	vert3_ = v3;
	set_material(mat);
}

bool Triangle::Hit(Ray r_, HitRecord &rec, float minHit, float maxHit) {
	Point3 edge1 = vert2() - vert1();
	Point3 edge2 = vert3() - vert1();

	Point3 p = Cross(r_.Direction(), edge2);
	float det = dot(edge1, p);

	// if((det > -EPSILON && det < EPSILON)) || (det < minHit || det > maxHit)) {
	if(det > -EPSILON && det < EPSILON) {
		return false;
	} else {
		float inv_det = 1.0 / det;
		Point3 t = r_.origin - vert1();
		float u = dot(t, p) * inv_det;
		
		if(u < 0.0 || u > 1.0) {
			return false;
		} else {
			Point3 q = Cross(t, edge1);
			float v = dot(r_.Direction(), q) * inv_det;

			if(v < 0.0 || u + v > 1.0) {
				return false;
			} else {
				float t = dot(edge2, q) * inv_det;
				rec.hit = r_.PointAt(t);;
				rec.normal = Cross(edge1, edge2);
				rec.mat = material();
				return true;
			}
		}
	}

	return false;
}