#ifndef _SHADER_H_
#define _SHADER_H_

#include "../utility/Vector3.h"
#include "../hitables/World.h"

using namespace hitables;

using utils::Vector3;

namespace shade {
  class Shader {
    public:
      RGB virtual GetColor( Ray r_, World world ) = 0;
    protected:
      int maxRef;
  };
} // namespace shade

#endif
