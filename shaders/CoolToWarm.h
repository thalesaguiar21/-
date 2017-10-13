#ifndef _COOLTOWARM_H_
#define _COOLTOWARM_H_

#include "Shader.h"

class CoolToWarm : public Shader {
  public:
    RGB GetColor( Ray r_, World world ) override;
};

#include "CoolToWarm.inl"

#endif
