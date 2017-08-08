#include <iostream>
#include "vec3.h"

using std::string;

int main(){
	vec3 a (1, 2, 3);
	vec3 b (2, 2, 3);
	vec3 c = a + b;
	float angle = get_degree(a, b, true);
	vec3::element_type t = dot(a, b);
	a *= 3;
	std::cout << "A = " << a <<std::endl;
	std::cout << "B = " << b <<std::endl;
	std::cout << "C = " << c <<std::endl;
	std::cout << "Angle AB = " << angle << std::endl;
	a.make_unit_vector();
	vec3 k = unit_vector(a);
	std::cout << "Â = " << a <<std::endl;
	std::cout << "||Â|| = " << a.length() <<std::endl;
	std::cout << "Â' = " << k <<std::endl;
	std::cout << "A . B = " << t <<std::endl;
	return 0;
}