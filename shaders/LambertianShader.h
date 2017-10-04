#ifndef _LAMBERT_SHADE_H_
#define _LAMBERT_SHADE_H_

#include "../utility/Vector3.h"
#include "../utility/Ray.h"
#include "Shader.h"

using utils::Vector3;
using utils::Ray;

class LambertianShader : public Shader {
  public:
    LambertianShader( void );
    LambertianShader( int maxRef_ );
    RGB GetColor( Ray r_, World world ) override;
  private:
    RGB GetColorAux(Ray r_, World world, int maxReflections );
};

#include "LambertianShader.inl"

#endif
