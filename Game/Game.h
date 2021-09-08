#pragma once

#include <iostream>
#include <string>
#include <SDL.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <assimp/config.h>

#include "Shader.h"
#include "Texture.h"
#include "Camera.h"
#include "Model.h"

class Game
{
public:
	Game();
	~Game();

private:
	bool _running;
	const int _SCR_WIDTH = 480;
	const int _SCR_HEIGHT = 480;
	SDL_Window* _window;
	SDL_GLContext _context;
	GLuint _vbo, _cubeVAO, _lightVAO, _ebo;
	const int _FPS = 60;
	float _dt;
	float _lastFrame;
	float timeValue = 0.0f;

	bool _pause = false;

	bool _firstMouse = true;
	float _lastX = _SCR_WIDTH / 2.0f;
	float _lastY = _SCR_HEIGHT / 2.0f;

	Camera _camera = Camera(glm::vec3(0.0f, 0.0f, 3.0f));

	Shader _shader;
	Shader _lightShader;

	glm::vec3 _lightPos = glm::vec3(1.2f, 1.0f, 2.0f);

	//Texture _texture = Texture("textures/container.png");
	//Texture _textureMap = Texture("textures/specularmap.png");
	Model teapot;

	void Init();
	void GameLoop();
	void Draw();
	void TakeInput();

};

