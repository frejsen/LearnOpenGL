#include "Texture.h"
#include <stb_image.h>

using namespace std;

Texture::Texture(std::string path)
{
	_path = path;
}

void Texture::Init()
{
	glGenTextures(1, &_texture);

	// Load textures
	int width, height, nrComponents;
	unsigned char* data = stbi_load(_path.c_str(), &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, _texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	}
	else {
		cerr << "Failed to load texture.\n";
	}
	stbi_image_free(data);
}

void Texture::Draw()
{
	if (_texture != NULL)
		glBindTexture(GL_TEXTURE_2D, _texture);
	else
		cerr << "Attempt to draw texture failed: Texture isn't initialized.\n";
}