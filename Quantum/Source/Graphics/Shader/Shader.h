#pragma once

#include "Core/Types.h"
#include <glad/gl.h>

namespace Quantum
{
	// TODO: Add shader caching
	class Shader
	{
	private:
		using ShaderSource = Dictionary<GLenum, const char*>;

		UInt32 m_RendererID;
		String m_Name;
	public:
		Shader(StringView path);
		Shader(const String& name, StringView vertexSource, StringView fragmentSource);
		~Shader();

		void Bind();
		void Unbind();

		const String& GetName() const { return m_Name; };

		void SetInt(StringView name, int value);
		void SetFloat(StringView name, float value);
		void SetFloat2(StringView name, const Vector2D& values);
		void SetFloat3(StringView name, const Vector3D& values);
		void SetFloat4(StringView name, const Vector4D& values);
		void SetMat3(StringView name, const Matrix3D& matrix);
		void SetMat4(StringView name, const Matrix4D& matrix);
	private:
		int GetUniformLocation(StringView name);
		void Compile(const ShaderSource& shaderSources);
	};
}
