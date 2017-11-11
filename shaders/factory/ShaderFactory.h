#ifndef _SHADER_FACTORY_H_
#define _SHADER_FACTORY_H_

#include "ShaderType.h"
#include "../BlinnPhongShader.h"
#include "../CoolToWarm.h"
#include "../DefaultShader.h"
#include "../NormalToColor.h"


class ShaderFactory {
	public:
		static Shader* Create(ShaderType type, float shaderValue);
};

#include "ShaderFactory.inl"


#endif // _SHADER_FACTORY_H_