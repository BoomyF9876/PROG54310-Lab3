#pragma once

#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "StandardIncludes.h"

class Camera
{
public:
	Camera(Resolution _resolution, float _fov = 45.0f, float _near = 0.1f, float _far = 1000.0f);
	~Camera() = default;

	void LookAt(const glm::vec3& _position, const glm::vec3& _lookAt, const glm::vec3& _up);

	glm::mat4 GetProjection() { return projection; }
	glm::mat4 GetView() { return view; }

private:
	glm::mat4 projection;
	glm::mat4 view;
};

#endif

