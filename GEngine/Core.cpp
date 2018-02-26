
// GLEW
#include <gl\glew.h>

//SOIL
#include <soil.h>

// GLFW
#include <GLFW\glfw3.h>

//GLM
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

// ����������� ��������� �
#include <stdlib.h>
#include <stdio.h> 
#include <string>
#include <fstream>
#include <sstream>

// ����������� ��������� .h
#include "Config.h"
#include "Shader.h"
#include "Callback.h"
#include "Core.h"

GLFWwindow* window;


class core
{
public:
	void glfw(GLint w, GLint h, const char name[])
	{
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		//glfwWindowHint(GLFW_DECORATED, GL_FALSE); // ����� ��� �����
		glfwWindowHint(GLFW_RESIZABLE, resizable);  // �������� �� ����������� ��������� ������� ����

		printf("glfwInit - Complete!\n");

		////////////////////////////////////////////////////////////////////
		//�������� ����
		window = glfwCreateWindow(w, h, "BEngin", nullptr, nullptr);
		if (window != nullptr)
		{
			glfwMakeContextCurrent(window);
			printf("Create GLFW window - Complete!\n");
		}
		else
		{
			glfwTerminate();
			printf("Create GLFW window - Failed\n");
		}
		////////////////////////////////////////////////////////////////////

		// Set the required callback functions
		glfwSetKeyCallback(window, key_callback);
		glfwSetWindowSizeCallback(window, window_size_callback);
		glfwSetCursorPosCallback(window, cursor_position_callback);

		// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
		glewExperimental = GL_TRUE;
		// Initialize GLEW to setup the OpenGL Function pointers
		glewInit();

		if (polygon_mod)
		{
			// �������� �� ����� �������� ��������� ���������. �.� ������ ������ �����
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		else
		{
			// �������� �� ����� ������ ��������� ���������. �.� ������ ������� ��������� � ���� ������
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
	}
};