#ifndef CORE_H
#define CORE_H

/*Запускается принажатии клавиш клавиатуры*/
/*esc - exit*/
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
/*Запускается при измениении координат курсора*/
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
/*Запускается при изменеиии размеров экрана*/
/*Изменяет пространство отрисовки*/
void window_size_callback(GLFWwindow* window, int width, int height);

class Core
{
public:
	/*окно*/
	GLFWwindow * window;
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
			VAO, // вершинный буфер
			EBO; //	объектный буфер

};

#endif // CORE_H


