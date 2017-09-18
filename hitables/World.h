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
      /*  Create a world limited from start to depth */
      World( vector<Hitable*> hitables_, float start, float depth);

      /*  Checks if the given Ray hit any hitable object on the world.
          The information of the first object that was hit is stored on
          the given HitRecord  object.

          @param Ray The ray being shooted inside the world
          @param HitRecord Where the information of a colision will be stored.
      */
      bool HitAnything( Ray r_, HitRecord &rec );
  };
} //namespace hitables

#include "World.inl"

#endif
