#include "Camera.h"

Camera::Camera(Resolution _resolution, float _fov, float _near, float _far)
{
	projection = glm::perspective(glm::radians(_fov),
		(float)_resolution.width / (float)_resolution.height,
		_near,
		_far);

	view = glm::lookAt(
		glm::vec3(1, 0, 0),
		glm::vec3(0, 0, 0),
		glm::vec3(0, 1, 0)
	);
}

void Camera::LookAt(const glm::vec3& _position, const glm::vec3& _lookAt, const glm::vec3& _up)
{
	view = glm::lookAt(_position, _lookAt, _up);
}
