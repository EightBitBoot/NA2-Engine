#pragma once

#include <string>
#include <unordered_map>

#include <stdio.h>

#include "glcommon.h"
#include "glmanager.h"

#include "math/mat4.h"

class Shader {
public:
	Shader(GLManager* manager, std::string filepath);
	~Shader();

	bool link();
	bool compile();

	void use();
	void unuse();

	GLint getUniformLocation(const std::string& name);
	void setUniformMat4f(const std::string& name, const mat4& data);
	void setUniform1f(const std::string& name, float data);

private:
	typedef struct ShaderSources { std::string vertexSource; std::string fragmentSource; } ShaderSources;

	ShaderSources parseShaderFile();
	void usePrevious();

private:
	std::unordered_map<std::string, GLint> m_uniformLocationCache;
	std::string m_filePath;

	GLManager* m_manager;

	ShaderSources m_shaderSources;

	GLuint m_handle;

	GLuint m_vertexShaderHandle;
	GLuint m_fragmentShaderHandle;
 
	bool m_inUse;
	bool m_isLinked;

};
