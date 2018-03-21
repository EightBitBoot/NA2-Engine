#include "graphics\shader.h"

namespace nat {
	Shader::Shader(GLManager* manager, std::string filepath) : m_manager(manager), m_handle(0), m_vertexShaderHandle(0), m_fragmentShaderHandle(0), m_filePath(filepath), m_inUse(false), m_isLinked(false)
	{
		GLCALL(m_handle = glCreateProgram());
		m_shaderSources = parseShaderFile();
	}

	Shader::~Shader() {}

	bool Shader::link()
	{
		GLCALL(glLinkProgram(m_handle));

		GLCALL(glDetachShader(m_handle, m_vertexShaderHandle));
		GLCALL(glDetachShader(m_handle, m_fragmentShaderHandle));

		GLCALL(glDeleteShader(m_vertexShaderHandle));
		GLCALL(glDeleteShader(m_fragmentShaderHandle));

		m_isLinked = true;

		return true;
	}

	bool Shader::compile()
	{
		const char* vertexSource = m_shaderSources.vertexSource.c_str();
		const char* fragmentSource = m_shaderSources.fragmentSource.c_str();

		GLCALL(m_vertexShaderHandle = glCreateShader(GL_VERTEX_SHADER));
		GLCALL(m_fragmentShaderHandle = glCreateShader(GL_FRAGMENT_SHADER));

		GLCALL(glShaderSource(m_vertexShaderHandle, 1, &vertexSource, NULL));
		GLCALL(glShaderSource(m_fragmentShaderHandle, 1, &fragmentSource, NULL));

		//Compile vertex shader and print compilation messages
		GLint success = 0;
		GLCALL(glCompileShader(m_vertexShaderHandle));
		GLCALL(glGetShaderiv(m_vertexShaderHandle, GL_COMPILE_STATUS, &success));
		if (success == GL_FALSE) {
			GLint logLength = 0;
			GLCALL(glGetShaderiv(m_vertexShaderHandle, GL_INFO_LOG_LENGTH, &logLength));
			char errorMessage[1024];
			GLCALL(glGetShaderInfoLog(m_vertexShaderHandle, 1024, &logLength, errorMessage));
			return false;
		}

		//Compile fragment shader and print compilation messages
		success = 0;
		GLCALL(glCompileShader(m_fragmentShaderHandle));
		GLCALL(glGetShaderiv(m_fragmentShaderHandle, GL_COMPILE_STATUS, &success));
		if (success == GL_FALSE) {
			GLint logLength = 0;
			GLCALL(glGetShaderiv(m_fragmentShaderHandle, GL_INFO_LOG_LENGTH, &logLength));
			char errorMessage[1024];
			GLCALL(glGetShaderInfoLog(m_fragmentShaderHandle, 1024, &logLength, errorMessage));
			return false;
		}

		GLCALL(glAttachShader(m_handle, m_vertexShaderHandle));
		GLCALL(glAttachShader(m_handle, m_fragmentShaderHandle));

		return true;
	}

	void Shader::use()
	{
		m_manager->useShader(m_handle);
		m_inUse = true;
	}

	void Shader::unuse()
	{
		m_manager->unuseShader();
		m_inUse = false;
	}

	GLint Shader::getUniformLocation(const std::string& name)
	{
		GLint location = -1;
		if (m_uniformLocationCache.find(name) == m_uniformLocationCache.end()) {
			GLCALL(location = glGetUniformLocation(m_handle, name.c_str()));
			m_uniformLocationCache[name] = location;
		}
		else {
			location = m_uniformLocationCache[name];
		}
		return location;
	}

	void Shader::setUniformMat4f(const std::string& name, const Mat4& data)
	{
		GLint location = getUniformLocation(name);
		if (location != -1) {
			if (!m_inUse) {
				use();
				GLCALL(glUniformMatrix4fv(location, 1, GL_TRUE, &data[0][0]));
				usePrevious();
			}
			else {
				GLCALL(glUniformMatrix4fv(location, 1, GL_TRUE, &data[0][0]));
			}
		}
	}

	void Shader::setUniform1f(const std::string& name, float data)
	{
		GLint location = getUniformLocation(name);
		if (location != -1) {
			if (!m_inUse) {
				use();
				GLCALL(glUniform1f(location, data));
				usePrevious();
			}
			else {
				GLCALL(glUniform1f(location, data));
			}
		}
	}

	Shader::ShaderSources Shader::parseShaderFile()
	{
		FILE* shaderFile = fopen(m_filePath.c_str(), "rt");

		fseek(shaderFile, 0, SEEK_END);
		unsigned long length = ftell(shaderFile);
		fseek(shaderFile, 0, SEEK_SET);

		char* contents = new char[length + 1];
		memset(contents, 0, sizeof(char) * (length + 1));
		fread(contents, 1, length, shaderFile);

		fclose(shaderFile);

		ShaderSources result;

		//THIS IS VERY TEMPORARY BETTER SYSTEM COMING
		std::string escapeString = "";
		bool vertexShader = false;
		bool fragmentShader = false;
		bool escapeCharacter = false;

		for (unsigned long i = 0; i < length; i++) {
			if (contents[i] == '#' && contents[i + 1] == 's') {
				vertexShader = false;
				fragmentShader = false;
				escapeCharacter = true;
				continue;
			}
			if (escapeCharacter && contents[i] == '\n') {
				escapeCharacter = false;
				escapeString = "";
				continue;
			}
			if (escapeCharacter) {
				escapeString += contents[i];
			}
			if (escapeString == "shader vertex") {
				vertexShader = true;
				fragmentShader = false;
				escapeString = "";
				continue;
			}
			else if (escapeString == "shader fragment") {
				vertexShader = false;
				fragmentShader = true;
				escapeString = "";
				continue;
			}
			if (vertexShader) {
				result.vertexSource += contents[i];
				continue;
			}
			if (fragmentShader) {
				result.fragmentSource += contents[i];
				continue;
			}
		}

		return result;
	}

	void Shader::usePrevious()
	{
		m_manager->usePreviousShader();
		m_inUse = false;
	}
}