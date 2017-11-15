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
	set_origin(Baricenter());
	edge1_ = vert2_ - vert1_;
	edge2_ = vert3_ - vert1_;
}

bool Triangle::Hit(Ray r_, HitRecord &rec, float minHit, float maxHit) {

	Point3 p = Cross(r_.Direction(), edge2());
	float det = dot(edge1(), p);

	if(det > -EPSILON && det < EPSILON) {
		return false;
	} else {
		float inv_det = 1.0 / det;
		Point3 t = r_.origin - vert1();
		float u = dot(t, p) * inv_det;
		
		if(u < 0.f || u > 1.f) {
			return false;
		} else {
			Point3 q = Cross(t, edge1());
			float v = dot(r_.Direction(), q) * inv_det;

			if(v < 0.f || u + v > 1.0) {
				return false;
			} else {
				float t = dot(edge2(), q) * inv_det;
				if(t < minHit || t > maxHit)
					return false;
				rec.root = t;
				rec.hit = r_.PointAt(t);
				rec.normal = UnitVector(Cross(edge2(), edge1()));
				rec.mat = material();
				return true;
			}
		}
	}

	return false;
}

Vector3 Triangle::RotateVerticle(Vector3 verticle, Vector3 target) {
	return Vector3(0.f);
}

Vector3 Triangle::TranslateVerticle(Vector3 verticle, Vector3 target) {
	Vector3 target_ = target - verticle;
  glm::vec4 trasnslade_vec (target_.X(), target_.Y(), target_.Z(), 1);
  glm::vec3 translation (verticle.X(), verticle.Y(), verticle.Z());
  glm::mat4 tMatrix = glm::translate(glm::mat4(1.0f), translation);
  glm::vec4 new_verticle = tMatrix * trasnslade_vec;

  return Vector3(new_verticle[0], new_verticle[1], new_verticle[2]);
}

Hitable* Triangle::Translate(Vector3 target) {
	Vector3 t_vert1 = TranslateVerticle(origin() - vert1(), target);
	Vector3 t_vert2 = TranslateVerticle(origin() - vert2(), target);
	Vector3 t_vert3 = TranslateVerticle(origin() - vert3(), target);

	return new Triangle(t_vert1, t_vert2, t_vert3, material());
}

Hitable* Triangle::Rotate(Vector3 angles) {
	glm::vec3 rotation (rad(angles.X()), rad(angles.Y()), rad(angles.Z()));
	glm::vec4 v1 (vert1().X(), vert1().Y(), vert1().Z(), 1);
	glm::vec4 v2 (vert2().X(), vert2().Y(), vert2().Z(), 1);
	glm::vec4 v3 (vert3().X(), vert3().Y(), vert3().Z(), 1);

	glm::mat4 model (v1, v2, v3, glm::vec4(0.0, 0.0, 0.0, 1.0));

	glm::mat4 rot = glm::rotate(model, angles.X(), glm::vec3(1.0, 0.0, 0.0));
	rot = glm::rotate(rot, angles.Y(), glm::vec3(0.0, 1.0, 0.0));
	rot = glm::rotate(rot, angles.Z(), glm::vec3(0.0, 0.0, 1.0));

	Point3 new_vert1 (rot[0][0], rot[1][0], rot[2][0]);
	Point3 new_vert2 (rot[0][1], rot[1][1], rot[2][1]);
	Point3 new_vert3 (rot[0][2], rot[1][2], rot[2][2]);
	return new Triangle(new_vert1, new_vert2, new_vert3, material());
}

Hitable* Triangle::Scale(Vector3 proportions) {
	Ray origin_v1 (origin(), vert1() - origin());
	Ray origin_v2 (origin(), vert2() - origin());
	Ray origin_v3 (origin(), vert3() - origin());

	Point3 new_vert1 = origin_v1.PointAt(proportions.X());
	Point3 new_vert2 = origin_v2.PointAt(proportions.Y());
	Point3 new_vert3 = origin_v3.PointAt(proportions.Z());

	return new Triangle(new_vert1, new_vert2, new_vert3, material());
}

Point3 Triangle::Baricenter() {
	Point3 half_edge1 = (vert2() + vert1()) * 0.5;
	Point3 half_edge2 = (vert3() + vert1()) * 0.5;

	Ray m1 (half_edge1, vert3());
	Ray m2 (half_edge2, vert2());
	
	float t = (m1.origin.X() - m2.origin.X()) / 
						(m2.Direction().X() - m1.Direction().X());
	return m1.PointAt(t);
}