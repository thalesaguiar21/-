#ifndef _COOLTOWARM_H_
#define _COOLTOWARM_H_

#include "Shader.h"

class CoolToWarm : public Shader {
  public:
  	CoolToWarm(void);
  	CoolToWarm(float value);
    RGB Color(Ray r_, World world, int depth) override;

  private:
  	float power_;
};

#include "CoolToWarm.inl"

#endif
