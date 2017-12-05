#include "Cube.h"

Cube::Cube() {
	side1_ = Vector3(1, 0, 0);
	side2_ = Vector3(0, 0, 1);
	side3_ = Cross(side1_, side2_);
	set_origin(Point3(0));
}

Cube::Cube(Point3 origin, Vector3 side1, Vector3 side2) {
	side1_ = side1;
	side2_ = side2;
	side3_ = Cross(side1_, side2_);
	set_origin(origin);
}

Cube::Cube(float xMin, float xMax, float yMin, float yMax, float zMin, 
				 	float zMax, Material *mat) {
	x_min = xMin;
	x_max = xMax;
	y_min = yMin;
	y_max = yMax;
	z_min = zMin;
	z_max = zMax;
	set_material(mat);
}

bool Cube::HitXY(Ray r_, HitRecord &rec, float minHit, float maxHit) {
	float k = zMin();
	float t = (k - r_.origin.Z()) / r_.Direction().Z();

	if(t < minHit || t > maxHit)
		return false;
	Point3 tmp = r_.PointAt(t);
	if(tmp.Y() < yMin() || tmp.Y() > yMax() ||
		 tmp.X() < xMin() || tmp.X() > xMax())
		return false;

	rec.root = t;
	rec.mat = material();
	rec.hit = r_.PointAt(t);
	rec.normal = Vector3(0,0,1);
	return true;
}

bool Cube::HitYZ(Ray r_, HitRecord &rec, float minHit, float maxHit) {
	float k = xMin();
	float t = (k - r_.origin.X()) / r_.Direction().X();

	if(t < minHit || t > maxHit)
		return false;
	Point3 tmp = r_.PointAt(t);
	if(tmp.Y() < yMin() || tmp.Y() > yMax() ||
		 tmp.Z() < zMin() || tmp.Z() > zMax())
		return false;

	rec.root = t;
	rec.mat = material();
	rec.hit = r_.PointAt(t);
	rec.normal = Vector3(1, 0, 0);
	return true;
}

bool Cube::HitXZ(Ray r_, HitRecord &rec, float minHit, float maxHit) {
	return false;
}

//xyhit
bool Cube::Hit(Ray r_, HitRecord &rec, float minHit, float maxHit) {

	bool hit_a_face = false;
	hit_a_face = HitXY(r_, rec, minHit, maxHit);
	hit_a_face = hit_a_face || HitYZ(r_, rec, minHit, maxHit);
	return hit_a_face;
}

Hitable* Cube::Translate(Vector3 target) {
	return new Cube();
}

Hitable* Cube::Rotate(Vector3 angles) {
	return new Cube();
}

Hitable* Cube::Scale(Vector3 proportions) {
	return new Cube();
}