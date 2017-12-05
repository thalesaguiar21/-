#ifndef _ANGLE_H_
#define _ANGLE_H_

#include <cmath>

namespace utils {
	#define PI 3.141592
	
  float rad(float angle) {
    return angle * PI / 180.0;
  }
}

#endif // namespace utils
