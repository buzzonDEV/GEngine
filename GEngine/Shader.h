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

	/*Загружает текстуру*/
	void load_texture() 
	{
		// Load and create a texture 
		glGenTextures(1, &texture1);
		glBindTexture(GL_TEXTURE_2D, texture1); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object
												// Set our texture parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		// Set texture filtering
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// Load, create texture and generate mipmaps
		int width, height;
		unsigned char* image = SOIL_load_image("debugc.png", &width, &height, 0, SOIL_LOAD_RGB);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);
		SOIL_free_image_data(image);
		glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.
	}

	/*Связывание текстур с использованием текстурных блоков*/
	void bind_texture()
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, this->texture1);
		glUniform1i(glGetUniformLocation(this->shaderProgram, "ourTexture1"), 0);
	}

private:
	GLuint texture1;
	GLuint texture2;
};