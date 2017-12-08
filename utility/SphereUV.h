#ifndef _SPHERE_UV_H_
#define _SPHERE_UV_H_


namespace utils {
	void GetSphereUV(const Vector3 &p, float &u, float &v) {
		Vector3 tmp_p = p;
		float phi = atan2(tmp_p.Z(), tmp_p.X());
		float theta = asin(tmp_p.Y());
		u = 1 - (phi + PI) / (2*PI);
		v = (theta + PI/2) / PI;
	}
}

#endif