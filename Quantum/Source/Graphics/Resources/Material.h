#pragma once

#include "Core/Types.h"
#include "Graphics/Shader/Shader.h"
#include "Texture.h"

namespace Quantum
{
	enum class TextureType
	{
		Diffuse,
		Specular,
		Normal,
		Emissive
	};

	class Material
	{
	private:
		Ref<Texture> m_DiffuseMap;
		Ref<Texture> m_SpecularMap;
		Ref<Texture> m_NormalMap;
		Ref<Texture> m_EmissiveMap;
		float m_Shininess;
		
		static Ref<Texture> s_DefaultTexture;
	public:
		Material(
			const Ref<Texture>& diffuseMap = nullptr,
			const Ref<Texture>& specularMap = nullptr,
			const Ref<Texture>& normalMap = nullptr,
			const Ref<Texture>& emissiveMap = nullptr,
			float shininess = 32.0f
		);

		void Bind(const Ref<Shader>& shader);

		void SetDiffuseMap(const Ref<Texture>& diffuseMap) { m_DiffuseMap = diffuseMap; };
		void SetSpecularMap(const Ref<Texture>& specularMap) { m_SpecularMap = specularMap; };
		void SetNormalMap(const Ref<Texture>& normalMap) { m_NormalMap = normalMap; };
		void SetEmissiveMap(const Ref<Texture>& emissiveMap) { m_EmissiveMap = emissiveMap; };
		void SetTexture(TextureType type, const Ref<Texture>& texture);
		void SetShininess(float shininess) { m_Shininess = shininess; };
	};
}
