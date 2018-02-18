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
		// Clear the colorbuffer
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Swap the screen buffers
		glfwSwapBuffers(window);
	}

}