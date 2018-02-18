#pragma once

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void window_size_callback(GLFWwindow* window, int width, int height);
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	//printf("X %g\tY %g\n",xpos,ypos);
	GR = xpos;
	GB = ypos;
}

void window_size_callback(GLFWwindow* window, int width, int height)
{
	glfwGetWindowSize(window, &Width, &Height);
	//printf("width %d\theight %d\n", Width, Height);
}