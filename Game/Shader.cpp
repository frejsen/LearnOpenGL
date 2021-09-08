#include "Shader.h"
#include <fstream>

using namespace std;

Shader::Shader()
{
}

Shader::~Shader()
{
	glDeleteShader(_vertex);
	glDeleteShader(_fragment);
}

void Shader::Use()
{
	glUseProgram(_program);
}

void Shader::Init(string vertexPath, string fragmentPath)
{
	_vertex = CreateShader(vertexPath, GL_VERTEX_SHADER);
	_fragment = CreateShader(fragmentPath, GL_FRAGMENT_SHADER);

	_program = glCreateProgram();

	glAttachShader(_program, _vertex);
	glAttachShader(_program, _fragment);
	glLinkProgram(_program);

	CheckCompileError(_program, "PROGRAM");
}

GLuint Shader::CreateShader(string fileName, GLenum type)
{
	string ogSource = LoadFile(fileName);

	const GLchar* source[1];
	source[0] = ogSource.c_str();
	GLint lengths[1];
	lengths[0] = ogSource.length();

	// Creates shader object
	GLuint shader = glCreateShader(type);

	// Compiles shader source code
	glShaderSource(shader, 1, source, lengths);
	glCompileShader(shader);

	CheckCompileError(shader, "SHADER");

	return shader;
}

string Shader::LoadFile(string fileName)
{
	ifstream file;

	file.open(fileName);

	string line;
	string output;
	while (file.is_open())
	{
		while (getline(file, line))
			output += line + '\n';
		file.close();
	}
	
	return output;
}

void Shader::CheckCompileError(GLuint shader, string type)
{
	GLint success;
	GLchar infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
}
