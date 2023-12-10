#include "Shader.h"

#include "Core/Core.h"
#include <glm/gtc/type_ptr.hpp>

namespace Quantum
{
	Shader::Shader(StringView path)
		: m_Name(FileSystemUtils::GetFileName(path))
	{
		ShaderSource sources;

		auto vertexPath = std::format("{}.vert.glsl", path);
		auto vertexSource = FileSystemUtils::ReadFile(vertexPath);
		sources[GL_VERTEX_SHADER] = vertexSource.c_str();

		auto fragmentPath = std::format("{}.frag.glsl", path);
		auto fragmentSource = FileSystemUtils::ReadFile(fragmentPath);
		sources[GL_FRAGMENT_SHADER] = fragmentSource.c_str();

		Compile(sources);
	}

	Shader::Shader(const String& name, StringView vertexSource, StringView fragmentSource)
		: m_Name(name)
	{
		ShaderSource sources;
		sources[GL_VERTEX_SHADER] = vertexSource.data();
		sources[GL_FRAGMENT_SHADER] = fragmentSource.data();
		Compile(sources);
	}

	Shader::~Shader()
	{
		glDeleteProgram(m_RendererID);
	}

	void Shader::Bind()
	{
		glUseProgram(m_RendererID);
	}

	void Shader::Unbind()
	{
		glUseProgram(0);
	}

	void Shader::SetInt(StringView name, int value)
	{
		glUniform1i(GetUniformLocation(name), value);
	}

	void Shader::SetFloat(StringView name, float value)
	{
		glUniform1f(GetUniformLocation(name), value);
	}

	void Shader::SetFloat2(StringView name, const Vector2D& values)
	{
		glUniform2f(GetUniformLocation(name), values.x, values.y);
	}

	void Shader::SetFloat3(StringView name, const Vector3D& values)
	{
		glUniform3f(GetUniformLocation(name), values.x, values.y, values.z);
	}

	void Shader::SetFloat4(StringView name, const Vector4D& values)
	{
		glUniform4f(GetUniformLocation(name), values.x, values.y, values.z, values.w);
	}

	void Shader::SetMat3(StringView name, const Matrix3D& matrix)
	{
		glUniformMatrix3fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void Shader::SetMat4(StringView name, const Matrix4D& matrix)
	{
		glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix));
	}

	int Shader::GetUniformLocation(StringView name)
	{
		return glGetUniformLocation(m_RendererID, name.data());
	}

	void Shader::Compile(const ShaderSource& shaderSources)
 	{
		LOG_CHECK(shaderSources.size() <= 2, Warning, LogGraphics, "Shader source count is greater than 2");

		auto program = glCreateProgram();

		List<GLuint> shaderIDs;
		for (const auto& [type, source] : shaderSources)
		{
			auto shader = glCreateShader(type);

			glShaderSource(shader, 1, &source, nullptr);
			glCompileShader(shader);

			auto isCompiled = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
			if (!isCompiled)
			{
				auto maxLength = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

				if (!maxLength)
					maxLength = 4096;

				List<char> infoLog(maxLength);
				glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

				glDeleteShader(shader);

				LOG(Error, LogGraphics, "Shader compilation failed: {}", infoLog.data());
				break;
			}

			glAttachShader(program, shader);
			shaderIDs.push_back(shader);
		}
		
		glLinkProgram(program);

		auto isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, &isLinked);
		if (!isLinked)
		{
			auto maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			if (!maxLength)
				maxLength = 4096;

			List<char> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			glDeleteProgram(program);

			for (auto id : shaderIDs)
				glDeleteShader(id);

			LOG(Error, LogGraphics, "Shader linking failed: {}", infoLog.data());
			return;
		}

		for (auto id : shaderIDs)
			glDetachShader(program, id);

		m_RendererID = program;
	}
}
