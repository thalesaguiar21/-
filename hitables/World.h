#ifndef _WORLD_H_
#define _WORLD_H_

#include <vector>

#include "Hitable.h"
#include "HitRecord.h"

#include "../scene/lights/Light.h"

using std::vector;

class World {
  public:
    vector<Hitable*> hitables;
    vector<Light*> lights;
    float start;
    float depth;

    /*  
        Create a world with objects, limited from the start to the end.
    */
    World( void );

    /*  
        Create a world with objects, limited from the start to the end.

        @param vector<Hitable*> List of objects int the world
        @param vector<Light*> LIst of world lights.
        @param float Begining of the world, minimum distance of Hitable objects
        @param float End of the world, maximum distance of Hitable objects
    */
    World( vector<Hitable*> hitables_, float start, float depth);

    /*  
        Create a world with objects and light, limited from the start to 
        the end.

        @param vector<Hitable*> List of objects int the world
        @param vector<Light*> LIst of world lights.
        @param float Begining of the world, minimum distance of Hitable objects
        @param float End of the world, maximum distance of Hitable objects
    */
    World( vector<Hitable*> hitables_, vector<Light*> lights_, float start,
           float depth);

    /*  
        Checks if the given Ray hit any hitable object on the world.
        The information of the first object that was hit is stored on
        the given HitRecord  object. this method uses the start and end
        values of the world  given in the instantiation.

        @param Ray The ray being shooted inside the world
        @param HitRecord Where the information of a colision will be stored.
    */
    bool HitAnything(Ray r_, HitRecord &rec);

    /*  
        Checks if the given Ray hit any hitable object on the world.
        The information of the first object that was hit is stored on
        the given HitRecord  object.

        @param Ray The ray being shooted inside the world
        @param HitRecord Where the information of a colision will be stored.
        @param Material The material of the object it hitted
        @param float Begining of the world, minimum distance of Hitable objects
        @param float End of the world, maximum distance of Hitable objects
    */
    bool HitAnything(Ray r_, HitRecord &rec, float from, float until);
};


#include "World.inl"

#endif
