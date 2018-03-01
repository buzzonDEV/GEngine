#include "Config.h"

// Позиция мыши
point	mouse;

// Размеры окна
int		Width = 960;	// Ширина
int		Height = 540;	// Высота

								// Параметры окна
bool	polygon_mod = false;	/* Ррежим отрисовки полигонов 
								true  - линиями
								false - полная отрисовка с двух сторон*/
bool	resizable = true;		// Разрешение изменения размера окна  