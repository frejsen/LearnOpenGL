#include "Game.h"
#include <fstream>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;

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
	_basicShader.Init("shaders/basic.vs", "shaders/basic.fs");

	// Depth buffer
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glClearColor(0.005f, 0.005f, 0.005f, 1.0f); // BLACK
	//glClearColor(0.995f, 0.995f, 0.995f, 1.0f); // WHITE

	// Transparency
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	SDL_SetRelativeMouseMode(SDL_TRUE);
	SDL_GL_SetSwapInterval(1);

	// Flip textures on startup since OpenGL flips them initially
	stbi_set_flip_vertically_on_load(true);

	teapot.init("models/teapot.obj");
	sphere.init("models/sphere.obj");

	_shader.Use();
	_shader.setBool("toonEnabled", true); // Enables toon shading
	_shader.setInt("levels", 6); // Toon shading levels

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
	SDL_GL_DeleteContext(_context);
	SDL_DestroyWindow(_window);
	SDL_Quit();
}

void Game::Draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Light position/color variables
	float colorG = 1.0f;
	float lightX = (2.0f * sin(timeValue) * 2);
	float lightY = (2.0f * sin(timeValue) + 2);
	float lightZ = (2.0f * cos(timeValue) * 2);
	glm::vec3 lightPos = glm::vec3(0.0f + lightX, 0.0f + lightY, 0.0f + lightZ);
	glm::vec3 lightColor = glm::vec3(lightX, colorG, lightZ); // Rainbow light
	//glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);

	_shader.Use();

	// Set matrices
	_shader.setVec3("lightPos", lightPos);
	_shader.setVec3("lightColor", lightColor);
	_shader.setVec3("viewPos", _camera.Position);
	_shader.setVec3("viewPos", _camera.Position);

	glColor3f(1, 0, 0); glVertex3f(0, 0, 0); glVertex3f(10, 0, 0);
	glColor3f(0, 1, 0); glVertex3f(0, 0, 0); glVertex3f(0, 10, 0);
	glColor3f(0, 0, 1); glVertex3f(0, 0, 0); glVertex3f(0, 0, 10);
	glEnd();
	glFlush();

	glm::mat4 projection = glm::perspective(glm::radians(_camera.Fov), (float)_SCR_WIDTH / (float)_SCR_HEIGHT, 0.1f, 100.0f);
	glm::mat4 view = _camera.GetViewMatrix();
	_shader.setMat4("projection", projection);
	_shader.setMat4("view", view);

	// Model loading
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, 1.0f, 0.0f)); // translate it down so it's at the center of the scene
	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down

	_shader.setMat4("model", model);

	_shader.Use();

	teapot.Draw(_shader);

	_lightShader.Use();

	_lightShader.setMat4("projection", projection);
	_lightShader.setMat4("view", view);
	_lightShader.setVec3("lightColor", lightColor);

	// Render light cube
	model = glm::mat4(1.0f);
	model = glm::translate(model, lightPos);
	model = glm::scale(model, glm::vec3(0.05f));

	_lightShader.setMat4("model", model);
	sphere.Draw(_lightShader);
}

void Game::TakeInput()
{
	if (!_pause)
	{
		// Repeated keys
		const Uint8* keystate = SDL_GetKeyboardState(NULL);
		if (keystate[SDL_SCANCODE_W] || keystate[SDL_SCANCODE_UP])
			_camera.Move(CameraMovement::FORWARD, _dt);
		if (keystate[SDL_SCANCODE_S] || keystate[SDL_SCANCODE_DOWN])
			_camera.Move(CameraMovement::BACKWARD, _dt);
		if (keystate[SDL_SCANCODE_A] || keystate[SDL_SCANCODE_LEFT])
			_camera.Move(CameraMovement::LEFT, _dt);
		if (keystate[SDL_SCANCODE_D] || keystate[SDL_SCANCODE_RIGHT])
			_camera.Move(CameraMovement::RIGHT, _dt);
		if (keystate[SDL_SCANCODE_SPACE])
			_camera.Move(CameraMovement::UP, _dt);
		if (keystate[SDL_SCANCODE_LSHIFT] || keystate[SDL_SCANCODE_RSHIFT])
			_camera.Move(CameraMovement::DOWN, _dt);
	}

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

			case SDLK_r:
				// View mode

				if (_viewMode == ViewMode::FILL) {
					glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
					_viewMode = ViewMode::WIREFRAME;
				}
				else if (_viewMode == ViewMode::WIREFRAME) {
					glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
					_viewMode = ViewMode::POINT;
				}
				else {
					glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
					_viewMode = ViewMode::FILL;
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