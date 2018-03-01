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



#endif // CORE_H


