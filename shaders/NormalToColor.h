#ifndef _NORMALTOCOLOR_H_
#define _NORMALTOCOLOR_H_

#include "../utils/Vec3.h"
#include "../utils/Ray.h"

#include "../scene/Scene.h"

#include "Shader.h"

class NormalToColor : public Shader {

public:
	NormalToColor () {
		// Nothing to initialize
	}

	/* Take the intersection between the given Ray and the objects in the scene
		 to create a normal vector and from this a color. 

		 @param Ray The ray being shooted at the scene.
		 @param Image The parameters of the img.
		 @param Scene A scene with a list of actors
		 @return RGB The color created from the normal vector.*/
	virtual RGB getColor(const Ray & r_, Image img, Scene scene) override {
		RGB color;
	  bool hitActor = false;
	  for(int i=0; i < scene.actors.size(); i++) {
	    if(scene.actors[i]->hit(r_)) {
	      color = scene.actors[i]->getNormal(r_);
	      hitActor = true;
	      break;
	    }
	  }

	  if(!hitActor) {
	    // If no Actor was hit, then hits the background.
	    auto unit = utility::unit_vector( r_.get_direction() );
	    auto tx = (unit.x() + 1.0) / 2.0;
	    auto ty = (unit.y() + 1.0) / 2.0;

	    RGB upper = (1 - tx) * img.upper_left + tx * img.upper_right;
	    RGB lower = (1 - tx) * img.lower_left + tx * img.lower_right;
	    color = (1 - ty) * lower + ty * upper;
	  }
	  return color;
	}
};

#endif