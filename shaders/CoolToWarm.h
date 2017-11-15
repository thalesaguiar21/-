#ifndef _COOLTOWARM_H_
#define _COOLTOWARM_H_

#include "Shader.h"

class CoolToWarm : public Shader {
  public:
  	CoolToWarm(void);
  	CoolToWarm(float value);

  protected:
    RGB OnHit(Ray r_, World world, HitRecord rec) override;
};

#include "CoolToWarm.inl"

#endif
