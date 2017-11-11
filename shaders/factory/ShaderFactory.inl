#include "ShaderFactory.h"

Shader* ShaderFactory::Create(ShaderType type, float shaderValue) {
	switch(type) {
		case ShaderType::blinnPhong: {
			return new BlinnPhongShader(shaderValue);
		}
		case ShaderType::coolToWarm: {
			return new CoolToWarm(shaderValue);
		}
		case ShaderType::defaultShader: {
			return new DefaultShader(shaderValue);
		}
		case ShaderType::normal2Color: {
			return new NormalToColor(shaderValue);
		}
	}
}