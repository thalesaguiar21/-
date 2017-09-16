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
      float start;
      float depth;

      World( void );
      World( vector<Hitable*> hitables_, float start, float depth);
      bool HitAnything( Ray r_, HitRecord &rec );
  };
} //namespace hitables

#include "World.inl"

#endif
