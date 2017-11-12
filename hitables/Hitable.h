#ifndef _HITABLE_H_
#define _HITABLE_H_

#include "../utility/Vector3.h"
#include "../utility/Ray.h"
#include "../materials/Material.h"
#include "HitRecord.h"

using utils::Vector3;
using utils::Ray;

class Hitable {
  public:
    /*  Checks if the given Ray instersect the object and stores
        the hit informations inside the given HitRecord.

        @param Ray The ray being shooted at the world.
        @param HitRecord The record to store the intersection information.
        @param float Minimum point of hit
        @param float Maximum point of hit
        @return bool True if it hit, false otherwise.
    */
    virtual bool Hit(Ray r_, HitRecord &rec, float minHit, float maxHit) = 0;

    Point3 origin() const { return origin_; };
    void set_origin(Point3 value) { origin_ = value; };
    Material* material() const { return mat_; };
    void set_material(Material *value) { mat_ = value; };
  
  private:
    Point3 origin_;
    Material *mat_;

};

#endif
