
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	mouse.x = xpos;
	mouse.y = ypos;
}

void window_size_callback(GLFWwindow* window, int width, int height)
{
	glfwGetWindowSize(window, &Width, &Height);

	// Define the viewport dimensions
	glfwGetFramebufferSize(window, &Width, &Height);
	glViewport(0, 0, Width, Height);
}