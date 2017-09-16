#include "World.h"

namespace hitables {
  World::World( void ) {
    // Empty world
  }

  World::World( vector<Hitable*> hitables_ ) {
    hitables = hitables_;
  }

  bool World::HitAnything( Ray r_, HitRecord &rec, float visibleWorld ) {
    HitRecord tmpRecord;
    float closestHit = visibleWorld;
    for(auto i=0; i<hitables.size(); i++) {
      if(hitables[i]->Hit(r_, tmpRecord)) {
        if (tmpRecord.root < closestHit && tmpRecord.root < visibleWorld) {
          closestHit = tmpRecord.root;
          rec = tmpRecord;
        }
        return true;
      }
    }
    return false;
  }
} //namespace hitables
