#ifndef _AREALIGHT_H_
#define _AREALIGHT_H_

class AreaLight : public Light {

public:
	AreaLight(void);
	AreaLight(Point3 center, Vector3 horizontal, Vector3 vertical);

	bool IsIlluminating(Point3 point) override;
	Ray GetShadowRay(Point3 surface) override;

	Vector3 horizontal() { return horizontal_; }
	Vector3 vertical() { return vertical_; }
private:
	Vector3 horizontal_;
	Vector3 vertical_;

	Point3 RandomInLightPlane();
};


#endif