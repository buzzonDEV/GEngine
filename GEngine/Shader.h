#ifndef SHADER_H
#define SHADER_H
class Shader
{
public:
	GLuint shaderProgram = glCreateProgram();

	/*Загружает код шейдера из файла и подключает к шейдерной программе */
	void load_shader(const char * file_path, int shader_type);

	/*Запускает шейдерную порграмму*/
	void use();

	/*Загружает текстуру*/
	void load_texture();

	/*Связывание текстур с использованием текстурных блоков*/
	void bind_texture();

private:
	GLuint texture1;
	GLuint texture2;
};
#endif // !SHADER_H