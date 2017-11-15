#include "Renderer.h"


// private:
// 	Image img;
// 	Camera *cam;
// 	World world;
// 	Shader *shader;
// int *linha, int row
Renderer::Renderer(void) {
	// Does nothing
}

Renderer::Renderer(Image img, Camera *cam, World world, Shader *shader) {
	this->img = img;
	this->cam = cam;
	this->world = world;
	this->shader = shader;
}

void Renderer::PrintExecutionTime(float time) {
  int min = int(time / CLOCKS_PER_SEC) / 60;
  int sec = int(time / CLOCKS_PER_SEC) - (min * 60);
  cout << "\n------------ TIME ---------------" << endl;
  cout << "Rendered file for " << min << "min " << sec << "s" << endl;
  cout << "---------------------------------" << endl;
}

void Renderer::ShowRenderingInfo(string file_specs, string msg) {
  cout << "\n------- FILE SPECFICATION -------" << endl;
  cout << file_specs << endl;
  cout << "---------------------------------" << endl;
  cout << msg << "..." <<flush;
}

void Renderer::RenderLine(int *mat_row, int width, int height, int alias_samp, 
											 int row, Camera *cam, Shader *shader, World world)	 {
	int kj = 0;
  RGB tonality (0.f);
  for(auto col = 0; col < width; col++) {
    tonality = RGB(0.f);
    for(auto s = 0; s < alias_samp; s++) {
      float u = float(col + drand48()) / float(width);
      float v = float(row + drand48()) / float(height);
      Ray r = cam->shootRay(u, v);;
      tonality += shader->GetColor(r, world);
    }

    tonality /= alias_samp;
    tonality = GammaCorrection(tonality, 2.0);
    
    mat_row[kj++] = int(255.99 * tonality.R()) ;      
    mat_row[kj++] = int(255.99 * tonality.G());
    mat_row[kj++] = int(255.99 * tonality.B());
  } 
}

void Renderer::Start(void) {
	std::clock_t before, after;
  ShowRenderingInfo(img.Description(), "\nRendering");
  vector<thread> threadPool;

  // Initialize rendering with a thread pool
  before = std::clock();
  for(auto row=img.height-1; row>=0; row--) {
    threadPool.push_back(thread(Renderer::RenderLine, std::ref(img.content[row]), 
    	img.width, img.height, img.aliasSamples, row, std::ref(cam), shader, 
    	world));
  }

  // Wait for threads to finish
  for(auto th = 0; th < threadPool.size(); th++){
    threadPool[th].join();
  }
  after = std::clock();
  
  cout << "Done!" << endl;
  PrintExecutionTime(float(after) - float(before));
}