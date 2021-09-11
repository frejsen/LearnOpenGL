#pragma once

#include <iostream>
#include <string>
#include <SDL.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <assimp/config.h>

#include "Shader.h"
#include "Camera.h"
#include "Model.h"

enum class ViewMode {
	FILL,
	WIREFRAME,
	POINT
};

class Game
{
public:
	Game();
	~Game();

private:
	void Init();
	void GameLoop();
	void Draw();
	void TakeInput();

	SDL_Window* _window;
	SDL_GLContext _context;
	bool _running;
	const int _SCR_WIDTH = 480;
	const int _SCR_HEIGHT = 480;
	const int _FPS = 60;
	float _dt;
	float _lastFrame;
	float timeValue = 0.0f;

	bool _pause = false;
	ViewMode _viewMode = ViewMode::FILL;

	float _lastX = _SCR_WIDTH / 2.0f;
	float _lastY = _SCR_HEIGHT / 2.0f;

	Camera _camera = Camera(glm::vec3(0.0f, 0.0f, 3.0f));

	Shader _shader;
	Shader _lightShader;
	Shader _basicShader;

	Model teapot;
	Model sphere;

};

