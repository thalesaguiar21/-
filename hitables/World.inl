#include "World.h"

World::World( void ) {
  // Empty world
}

World::World( vector<Hitable*> hitables_, float start_, float depth_ ) {
  hitables = hitables_;
  start = start_;
  depth = depth_;
}

World::World( vector<Hitable*> hitables_, vector<Light*> lights_, float start_,
              float depth_ ) {
  hitables = hitables_;
  start = start_;
  depth = depth_;
  lights = lights_;
}

bool World::HitAnything( Ray r_, HitRecord &rec ) {
  HitRecord tmpRecord;
  double closest = depth;
  for(auto i=0; i<hitables.size(); i++) {
    if(hitables[i]->Hit(r_, tmpRecord, start, depth)) {
      closest = tmpRecord.root;
      rec = tmpRecord;
      return true;
    }
  }
  return false;
}
