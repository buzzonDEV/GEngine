//file is MAIN.cpp
#include "Core.h"

int main(int argc, char *argv[])
{
	//инициаизация и создание окна
	glfw(Width, Height, "BEngin");

	// Game loop
	while (!glfwWindowShouldClose(window))
	{
		//Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		// Render
		render render;
		render.clear_color(GR/Width,GB/Height);

 
		// Swap the screen buffers
		glfwSwapBuffers(window);
	}
}