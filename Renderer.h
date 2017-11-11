#ifndef _MY_RENDERER_H_
#define _MY_RENDERER_H_

#include <vector>
#include <string.h>
#include <thread>
#include <time.h>

#include "scene/cameras/Camera.h"
#include "file_reader/Image.h"
#include "shaders/Shader.h"
#include "hitables/Hitable.h"
#include "utility/Gamma.h"

using namespace filerd;

using std::string;
using std::vector;
using std::thread;	
using std::cout;
using std::endl;
using std::flush;

using utils::GammaCorrection;

class Renderer {
private:
	Image img;
	Camera *cam;
	World world;
	Shader *shader;

	static void RenderLine(int *mat_row, int width, int height, int alias_samp, 
		int row, Camera *cam, Shader *shader, World world); 
	 
	void ShowRenderingInfo(string file_specs, string msg);
	void PrintExecutionTime(float time);
public:
	Renderer(void);
	Renderer(Image img, Camera *cam, World world, Shader *shader);
	void Start(void);
};

#include "Renderer.inl"

#endif