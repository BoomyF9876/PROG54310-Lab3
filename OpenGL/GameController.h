#pragma once

#ifndef _GAMECONTROLLER_H_
#define _GAMECONTROLLER_H_

#include "StandardIncludes.h"
#include "Shader.h"
#include "Mesh.h"
#include "Camera.h"

class GameController
{
public:
	GameController() = default;
	~GameController() = default;

	void Initialize();
	void RunGame();

private:
	Shader* shader = nullptr;
	Mesh* mesh = nullptr;
	Camera* camera = nullptr;
};

#endif

