#ifndef _WORLD_H_
#define _WORLD_H_

#include "Hitable.h"
#include "HitRecord.h"
#include <vector>

using std::vector;

namespace hitables {
  class World {
    public:
      vector<Hitable*> hitables;

      World( void );
      World( vector<Hitable*> hitables_ );
      bool HitAnything( Ray r_, HitRecord &rec, float visibleWorld );
  };
} //namespace hitables

#include "World.inl"

#endif
