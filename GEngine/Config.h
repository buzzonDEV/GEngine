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
extern bool	polygon_mod;	/*	Ррежим отрисовки полигонов 
								true  - линиями
								false - полная отрисовка с двух сторон*/

extern bool	resizable;		// Возможность изменения размера окна  

#endif // !CONFIG_H
