#ifndef CORE_H
#define CORE_H

/*Запускается при нажатии клавиш*/
void key_callback(GLFWwindow* main_window, int key, int scancode, int action, int mode);
/*Запускается при измениении координат курсора в области окна*/
void cursor_position_callback(GLFWwindow* main_window, double xpos, double ypos);
/*Запускается при изменеиии размеров экрана*/
void window_size_callback(GLFWwindow* main_window, int width, int height);


// Определяет несколько возможных вариантов движения камеры. 
enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

class Core
{
public:
	GLuint VAO;
	GLFWwindow * main_window; // главное окно
	/*Конструктор создани окна. Получаемые параметры w - стартовая ширина окна
	h - стартоваяя высота окна
	name - название процесса*/
	Core(GLint w, GLint h, const char name[]);

	/*Удаляет отработавшие буферы, переводит в режим терминала*/
	~Core();

	/*Создает буферы*/
	void create_beffers();

	/*Удаляет буверы*/
	void remove_buffers();

	/*Обновляет изображение*/
	void render();

private:
	GLuint  VBO, // вершинный буфер
			EBO; //	объектный буфер

};

#endif // CORE_H


