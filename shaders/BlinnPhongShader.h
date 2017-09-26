#ifndef _BLINNPHONG_SHADER_H_
#define _BLINNPHONG_SHADER_H_

#include "../utility/Vector3.h"
#include "../utility/Ray.h"
#include "Shader.h"

using utils::Vector3;
using utils::Ray;

namespace shade {
  class BlinnPhongShader : public Shader {
    public:
      BlinnPhongShader( Vector3 reflections );
      RGB GetColor( Ray r_, World world );
  };
} // namespace shade

#endif
