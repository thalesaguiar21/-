#ifndef _MY_RENDERER_H_
#define _MY_RENDERER_H_

#include <vector>
#include <string.h>
#include <thread>
#include <time.h>

#include "scene/cameras/Camera.h"
#include "file_reader/Image.h"
#include "hitables/Hitable.h"
#include "utility/Gamma.h"
#include "shading_models/models/ShadingService.h"

using namespace filerd;

using std::string;
using std::vector;
using std::thread;	
using std::cout;
using std::endl;
using std::flush;

using utils::GammaCorrection;

class Renderer {
	public:
		Renderer(void);
		Renderer(Image img, Camera *cam, World world);
		void Start(void);

	private:
		Image img;
		Camera *cam;
		World world;

		static void RenderLine(int *mat_row, int width, int height, int alias_samp, 
			int row, Camera *cam, World world); 		 
		void ShowRenderingInfo(string file_specs, string msg);
		void PrintExecutionTime(float time);

};

#include "Renderer.inl"

#endif