#ifndef CONFIG_H
#define CONFIG_H

/*double x y*/
struct point
{
	double x;
	double y;
};

// Позиция мыши
extern point	mouse;

// Размеры окна
extern int		Width;	// Ширина главного окна
extern int		Height;	// Высота главного окна

							// Параметры окна
extern bool	polygon_mod;	/* Режим отрисовки полигонов 
							   true  - линиями
							   false - полная отрисовка с двух сторон*/
extern bool	resizable;		// Разрешение изменения размера окна  

// Настройки камеры
extern const float YAW;
extern const float PITCH;
extern const float SPEED;
extern const float SENSITIVTY;
extern const float ZOOM;

#endif // !CONFIG_H
