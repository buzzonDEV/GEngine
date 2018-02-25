class Shader
{
public:
	GLuint shaderProgram = glCreateProgram();

	/*Загружает код шейдера из файла и подключает к шейдерной программе */
	void load_shader(const char * file_path, int shader_type)
	{
		// Загрузка кода шейдера из файла
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

		// Сборка шейдеров
		GLuint shader = glCreateShader(shader_type);
		GLint success;
		char const * VertexSourcePointer = shaderCode.c_str();
		glShaderSource(shader, 1, &VertexSourcePointer, NULL);
		glCompileShader(shader);

		// Проверка сборки
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			printf("ERROR::SHADER::%d::COMPILATION_FAILED\n", shader_type);
		}

		// Присоединение шейдеров к программе
		glAttachShader(this->shaderProgram, shader);
		glLinkProgram(this->shaderProgram);

		glGetProgramiv(this->shaderProgram, GL_LINK_STATUS, &success);
		if (!success)
		{
			printf("ERROR::SHADER::PROGRAM::LINKING_FAILED\n");
		}

		// Очистка программы от присоединенного шейдера
		glDeleteShader(shader);
	}

	/*Запускает шейдерную порграмму*/
	void use()
	{
		glUseProgram(this->shaderProgram);
	}

private:

};


