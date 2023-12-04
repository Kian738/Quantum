#pragma once

#include "Core/Types.h"
#include "Graphics/Buffers/Buffer.h"

namespace Quantum
{
	struct Vertex
	{
		Vector3D Position;
		Vector3D Normal;
		Vector2D TexCoord;

		static BufferLayout GetLayout()
		{
			return
			{
				{ ShaderDataType::Float3, "a_Position" },
				{ ShaderDataType::Float3, "a_Normal" },
				{ ShaderDataType::Float2, "a_TexCoord" }
			};
		};
	};

}
