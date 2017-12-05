#ifndef _CUBE_H_
#define _CUBE_H_

// XZ RECT

class Cube : public Hitable {

	public:
		Cube();
		Cube(Point3 origin, Vector3 side1, Vector3 side2);
		Cube(float xMin, float xMax, float yMin, float yMax, float zMin, 
				 float zMax, Material *mat);
		//xzhit
		bool Hit(Ray r_, HitRecord &rec, float minHit, 
             float maxHit) override;
    Hitable* Translate(Vector3 target) override;
    Hitable* Rotate(Vector3 angles) override;
    Hitable* Scale(Vector3 proportions) override;

    Vector3 side1() const { return side1_; }
    void set_side1(Vector3 value) { side1_ = value; } 
    Vector3 side2() const { return side2_; }
    void set_side2(Vector3 value) { side2_ = value; }
    Vector3 side3() const { return side3_; }
    void set_side3(Vector3 value) { side3_ = value; }

  private:
  	float xMin() const { return x_min; }
  	float xMax() const { return x_max; }
  	float yMin() const { return y_min; }
  	float yMax() const { return y_max; }
  	float zMin() const { return z_min; }
  	float zMax() const { return z_max; }

  	bool HitXY(Ray r_, HitRecord &rec, float minHit, float maxHit);
  	bool HitYZ(Ray r_, HitRecord &rec, float minHit, float maxHit);
  	bool HitXZ(Ray r_, HitRecord &rec, float minHit, float maxHit);  	

  	float x_min, x_max;
  	float y_min, y_max;
  	float z_min, z_max;
  	Vector3 side1_;
  	Vector3 side2_;
  	Vector3 side3_;
};

#include "Cube.inl"

#endif // _CUBE_H_