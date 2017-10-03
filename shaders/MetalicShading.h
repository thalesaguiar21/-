#ifndef _METALICSHADING_H_
#define _METALICSHADING_H_

namespace shade {

	class MetalicShading : public Shader {
		public:
			MetalicShading ( void );
			MetalicShading ( int reflections );
      RGB GetColor( Ray r_, World world ) override;
   	private:
   		RGB GetColorAux( Ray r_, World world, int maxRef_ );

	};

} // namespace shade

#include "MetalicShading.inl"

#endif