#include "glm/fwd.hpp"
#include "mxpch.h"
#include "DirectionalLight.h"

#define GLM_ENABLE_EXPERIMENTAL
#include<glm/gtx/vector_angle.hpp>

namespace RenderingEngine
{
	DirectionalLight::DirectionalLight()
	{
		const glm::mat4 ortho = glm::ortho(-30.0f, 30.0f, -30.0f, 30.0f, 0.01f, 100.0f);
		const glm::mat4 view = glm::lookAt(m_Parameters.Position, glm::vec3(0), glm::vec3(0, 1, 0));
		const glm::mat4 model = glm::mat4(1.0f);

		m_Parameters.LightMat = glm::mat4(ortho * view * model);
	}
}