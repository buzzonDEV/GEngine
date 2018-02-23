// Shaders
#include <string>
#include <fstream>
#include <sstream>

class Shader
{
public:
	void load_shader(const char * file_path, int shader_type)
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
		else
		{
			printf("ERROR::SHADER::LOAD_FAILED\n");
		}
		GLint success;
		//сборка шейдеров
		GLuint shader = glCreateShader(shader_type);
		char const * VertexSourcePointer = shaderCode.c_str();
		glShaderSource(shader, 1, &VertexSourcePointer, NULL);
		glCompileShader(shader);
		// Проверка загрузки
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			printf("ERROR::SHADER::%d::COMPILATION_FAILED\n", shader_type);
		}
		// присоединение шейдеров
		glAttachShader(this->shaderProgram, shader);
		glLinkProgram(this->shaderProgram);

		glGetProgramiv(this->shaderProgram, GL_LINK_STATUS, &success);
		if (!success)
		{
			printf("ERROR::SHADER::PROGRAM::LINKING_FAILED\n");
		}

		// удаление созданных шейдеров
		glDeleteShader(shader);
	}
	void use()
	{
		glUseProgram(this->shaderProgram);
	}


private:
	GLuint shaderProgram = glCreateProgram();
};


