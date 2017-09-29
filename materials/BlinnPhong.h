#ifndef _BLINNPHONG_MAT_H_
#define _BLINNPHONG_MAT_H_

#inlcude "Material.h"

namespace materials {
  class BlinnPhong : public Material {
  public:
    BlinnPhong ( Vector3 albedo, float absorption );
    bool Diffusion( Ray incident, Ray &diffused, Point3 hitPoint,
                    Vector3 normal ) override;
  protected:
    Vector3 Reflect( Ray incident, Vector3 normal ) override;
  };
} // namespace materials

#endif
