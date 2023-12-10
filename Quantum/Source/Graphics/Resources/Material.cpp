#include "Material.h"

#include "Core/Core.h"

namespace Quantum
{
	Material::Material(
		const Ref<Texture>& diffuseMap,
		const Ref<Texture>& specularMap,
		const Ref<Texture>& normalMap,
		const Ref<Texture>& emissiveMap,
		float shininess,
		const Ref<Texture>& defaultTexture
	)
		: m_DiffuseMap(COALESCE(diffuseMap, defaultTexture))
		, m_SpecularMap(COALESCE(specularMap, defaultTexture))
		, m_NormalMap(COALESCE(normalMap, defaultTexture))
		, m_EmissiveMap(COALESCE(emissiveMap, defaultTexture))
		, m_Shininess(shininess)
	{
	}

	void Material::Bind(const Ref<Shader>& shader)
	{
		shader->Bind();

		m_DiffuseMap->Bind(0);
		shader->SetInt("u_Material.diffuse", 0);

		m_SpecularMap->Bind(1);
		shader->SetInt("u_Material.specular", 1);
		shader->SetFloat("u_Material.shininess", m_Shininess);

		m_NormalMap->Bind(2);
		shader->SetInt("u_Material.normal", 2);

		m_EmissiveMap->Bind(3);
		shader->SetInt("u_Material.emissive", 3);
	}

	void Material::SetTexture(TextureType type, const Ref<Texture>& texture)
	{
		switch (type)
		{
			case TextureType::Diffuse:
				m_DiffuseMap = texture;
				break;
			case TextureType::Specular:
				m_SpecularMap = texture;
				break;
			case TextureType::Normal:
				m_NormalMap = texture;
				break;
			case TextureType::Emissive:
				m_EmissiveMap = texture;
				break;
			default:
				LOG(Error, LogGraphics, "Unknown texture type: {}", static_cast<int>(type));
		}
	}
}
