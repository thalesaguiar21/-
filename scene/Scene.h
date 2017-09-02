#ifndef _SCENE_H_
#define _SCENE_H_

#include <iostream>
#include <vector>

#include "Actor.h"
#include "Camera.h"

#include "../utils/Vec3.h"

using std::vector;

class Scene 
{
public:
	// The camera from where the Rays will be shooted
	Camera cam;
	// The scene's actors
	vector<Actor*> actors;

	Scene () 
	{
		cam = Camera(Point3(0, 0, 0), Point3(0, 0, 0), Vec3(0, 0, 0), Vec3(0, 0, 0));
	}

	/* Creates a new scene with the given camera and a set of
		 actors. These actors are sorted by their z coordinate of their origin.*/
	Scene (Camera camera, vector<Actor*> actors) 
	{
	  cam = camera;
	  this->actors = actors;
	  sortActors();
	}

	/* Sort the scene's actors by ther Z coordinate of their origin.*/
	inline void sortActors() 
	{
		if(actors.size() > 1) {
			for(int i=0; i < actors.size(); i++) {
				for(int j=i; j<actors.size(); j++) {
					if(actors[j]->origin.z() < actors[i]->origin.z()){
						Actor *aux = actors[i];
						actors[i] = actors[j];
						actors[j] = aux;
					}
				}
			}
		}
	}
};
#endif
