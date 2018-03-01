#ifndef CONFIG_H
#define CONFIG_H

struct point
{
	double x;
	double y;
};

// Позиция мыши
extern point	mouse;
// Размеры окна
extern int		Width;	// Ширина
extern int		Height;	// Высота
						// Параметры окна
extern bool	polygon_mod;	// Отвечает за режим отрисовки полигонов
extern bool	resizable;		// Отвечает за возможность изменения размера окна  

#endif // !CONFIG_H
