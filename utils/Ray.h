#ifndef _RAY_H_ 
#define _RAY_H_ 
#include "Vec3.h"  // necessário para acessar Vec3 
using namespace utility; 

class Ray 
{     
private:         
	Point3 O; // the origin of the ray.         
	Vec3 D; // The ray's direction.     

public:         
	//=== Alias         
	typedef float real_type;         
	//=== Special members         
	Ray( Point3 o_=Point3(), Vec3 d_=Vec3() ) : O( o_ ), D( d_ ) { /* empty */ }         
	//=== Access methods         
	
	inline Vec3 get_direction( void ) const 
	{ 
		return D; 
	}

	inline Point3 get_origin( void ) const 
	{ 
		return O; 
	}
	
	Point3 point_at( real_type t_ )  const 
	{ 
		return O + t_ * D; // parametric equation of the ray.
	} 
}; 
#endif

