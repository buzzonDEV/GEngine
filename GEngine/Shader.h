// Shaders
#include <string>
#include <fstream>
#include <sstream>


void load_shader(GLuint *shaderProgram, const char * file_path, int shader_type)
{
	// Загружаем код Вершинного Шейдера из файла
	std::string shaderCode;
	std::ifstream shaderStream(file_path, std::ios::in);
	if (shaderStream.is_open())
	{
		std::stringstream sstr;
		sstr << shaderStream.rdbuf();
		shaderCode = sstr.str();
		shaderStream.close();
	}

	//сборка шейдеров
	GLuint shader = glCreateShader(shader_type);
	char const * VertexSourcePointer = shaderCode.c_str();
	glShaderSource(shader, 1, &VertexSourcePointer, NULL);
	glCompileShader(shader);

	// присоединение шейдеров
	glAttachShader((*shaderProgram), shader);
	glLinkProgram((*shaderProgram));

	// удаление созданных шейдеров
	glDeleteShader(shader);
}
