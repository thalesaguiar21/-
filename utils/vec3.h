#ifndef VEC3_H
#define VEC3_H

class vec3 {
public:
	typedef float coord_type;
	coord_type values[3];
	enum element { X=0, Y=1, Z=2, R=0, G=1, B=2 };

	vec3(coord_type x, coord_type y, coord_type z) {
		values[X] = x;
		values[Y] = y;
		values[Z] = z;
	}

	inline coord_type x() { return values[X]; }
	inline coord_type y() { return values[Y]; }
	inline coord_type z() { return values[Z]; }
	inline coord_type r() { return values[R]; }
	inline coord_type g() { return values[G]; }
	inline coord_type b() { return values[B]; }
};

#endif