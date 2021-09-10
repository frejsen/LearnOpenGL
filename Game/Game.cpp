#include "Game.h"
#include <fstream>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;

float vertices[] = {
	// positions          // normals           // texture coords
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
};

glm::vec3 cubePositions[] = {
	glm::vec3(0.0f,  0.0f,  0.0f),
	glm::vec3(2.0f,  5.0f, -15.0f),
	glm::vec3(-1.5f, -2.2f, -2.5f),
	glm::vec3(-3.8f, -2.0f, -12.3f),
	glm::vec3(2.4f, -0.4f, -3.5f),
	glm::vec3(-1.7f,  3.0f, -7.5f),
	glm::vec3(1.3f, -2.0f, -2.5f),
	glm::vec3(1.5f,  2.0f, -2.5f),
	glm::vec3(1.5f,  0.2f, -1.5f),
	glm::vec3(-1.3f,  1.0f, -1.5f)
};

float coordinates[] = {
	0.0f, 1.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 1.0f
};

unsigned int indices[] = {
	0, 1, 3, // first triangle
	1, 2, 3  // second triangle
};

Game::Game()
{
	Init();
}

Game::~Game()
{
}

void Game::Init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		cout << "SDL failed to initialize: " << SDL_GetError() << endl;

	_window = SDL_CreateWindow(
		"LearnOpenGL",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		_SCR_WIDTH,
		_SCR_HEIGHT,
		SDL_WINDOW_OPENGL
	);

	_context = SDL_GL_CreateContext(_window);

	GLenum error = glewInit();
	if (error != GLEW_OK)
		cerr << "GLEW failed to initialize: " << glewGetErrorString(error) << endl;

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

	_shader.Init("shaders/model_loading.vs", "shaders/model_loading.fs");
	//_shader.Init("shaders/models/shader.vs", "shaders/models/shader.fs");
	_lightShader.Init("shaders/light.vs", "shaders/light.fs");

	// Generates OpenGL objects
	glGenVertexArrays(1, &_cubeVAO);
	glGenBuffers(1, &_vbo);
	//glGenBuffers(1, &_ebo);

	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(_cubeVAO);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture coords attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glGenVertexArrays(1, &_lightVAO);
	glBindVertexArray(_lightVAO);

	glBindBuffer(GL_ARRAY_BUFFER, _vbo);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Depth buffer
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glClearColor(0.005f, 0.005f, 0.005f, 1.0f); // BLACK
	//glClearColor(0.995f, 0.995f, 0.995f, 1.0f); // WHITE

	// Transparency
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Wireframe mode
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	SDL_SetRelativeMouseMode(SDL_TRUE);
	SDL_GL_SetSwapInterval(1);

	// Flip textures on startup since OpenGL flips them initially
	stbi_set_flip_vertically_on_load(true);

	teapot.init("models/teapot.obj");

	_shader.Use();

	GameLoop();
}

void Game::GameLoop()
{
	_running = true;

	while (_running)
	{
		float currentFrame = SDL_GetTicks();
		_dt = currentFrame - _lastFrame;
		_lastFrame = currentFrame;

		timeValue += 0.005f;

		TakeInput();
		Draw();
		SDL_Delay(3);

		SDL_GL_SwapWindow(_window);
	}

	_shader.~Shader();
	_lightShader.~Shader();
	glDeleteVertexArrays(1, &_lightVAO);
	glDeleteVertexArrays(1, &_cubeVAO);
	glDeleteBuffers(1, &_vbo);
	//glDeleteBuffers(1, &_ebo);
	SDL_GL_DeleteContext(_context);
	SDL_DestroyWindow(_window);
}

void Game::Draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Light position/color variables
	float colorG = 1.0f;
	float lightX = 2.0f * sin(timeValue) * 2;
	float lightY = 1.5f * sin(timeValue) * 2;
	float lightZ = 2.0f * cos(timeValue) * 2;
	glm::vec3 lightPos = glm::vec3(lightX, lightY, lightZ);
	//glm::vec3 lightColor = glm::vec3(lightX, colorG, lightZ);
	glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);

	_shader.Use();

	// Set matrices
	_shader.setVec3("lightPos", lightPos);
	_shader.setVec3("lightColor", lightColor);
	_shader.setVec3("viewPos", _camera.Position);
	_shader.setVec3("viewPos", _camera.Position);

	// pass projection matrix to shader (note that in this case it could change every frame)
	glm::mat4 projection = glm::perspective(glm::radians(_camera.Fov), (float)_SCR_WIDTH / (float)_SCR_HEIGHT, 0.1f, 100.0f);
	_shader.setMat4("projection", projection);
	// camera/view transformation
	glm::mat4 view = _camera.GetViewMatrix();
	_shader.setMat4("view", view);

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
	_shader.setMat4("model", model);
	teapot.Draw(_shader);

	/*glm::mat4 outsideModel = glm::mat4(1.0f);
	outsideModel = glm::mat4(1.0f);
	outsideModel = glm::translate(outsideModel, glm::vec3(0.0f, 0.0f, 0.0f));
	outsideModel = glm::scale(outsideModel, glm::vec3(35.0f, 35.0f, 35.0f));
	_lightShader.setMat4("model", outsideModel);
	glBindVertexArray(_cubeVAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);*/

	_lightShader.Use();
	_lightShader.setMat4("projection", projection);
	_lightShader.setMat4("view", view);
	_lightShader.setVec3("lightColor", lightColor);

	// Render light cube
	model = glm::mat4(1.0f);
	model = glm::translate(model, lightPos);
	model = glm::scale(model, glm::vec3(0.2f));

	_lightShader.setMat4("model", model);

	glBindVertexArray(_lightVAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void Game::TakeInput()
{
	const Uint8* keystate = SDL_GetKeyboardState(NULL);
	if (keystate[SDL_SCANCODE_W])
		_camera.Move(FORWARD, _dt);
	if (keystate[SDL_SCANCODE_S])
		_camera.Move(BACKWARD, _dt);
	if (keystate[SDL_SCANCODE_A])
		_camera.Move(LEFT, _dt);
	if (keystate[SDL_SCANCODE_D])
		_camera.Move(RIGHT, _dt);

	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym) {
			case SDLK_ESCAPE:
				if (_pause != true) {
					SDL_SetRelativeMouseMode(SDL_FALSE);
					_pause = true;
				} else {
					SDL_SetRelativeMouseMode(SDL_TRUE);
					_pause = false;
				}
				break;
			default:
				break;
			}
		} else if (event.type == SDL_QUIT) {
			_running = false;
		} else if (event.type == SDL_MOUSEMOTION && _pause != true) {
			_camera.ProcessMouseMovement(event.motion.xrel, -event.motion.yrel);
		} else if (event.type == SDL_MOUSEBUTTONDOWN) {
			if (_pause == true) {
				SDL_SetRelativeMouseMode(SDL_TRUE);
				_pause = false;
			}
		}
	}
}