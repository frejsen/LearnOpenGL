#pragma once

#include <iostream>
#include <string>
#include <GL/glew.h>

class Texture
{
public:
	Texture(std::string path);
	unsigned int getTexture() { return _texture; }

	void Init();
	void Draw();

private:
	unsigned int _texture;
	std::string _path;

};

