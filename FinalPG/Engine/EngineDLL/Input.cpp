#include "Input.h"
#include <GLFW\glfw3.h>

Input::Input(Window *window)
{
	win = window;
}


bool Input::IsKeyPressed(int i)
{
	if (glfwGetKey((GLFWwindow*)win->GetWindow(), i) == GLFW_PRESS) //87 w /UP 265
		return true;
	if (glfwGetKey((GLFWwindow*)win->GetWindow(), i) == GLFW_PRESS)//83 s /DOWN 264
		return true;
	if (glfwGetKey((GLFWwindow*)win->GetWindow(), i) == GLFW_PRESS)//65 a/left 263
		return true;
	if (glfwGetKey((GLFWwindow*)win->GetWindow(), i) == GLFW_PRESS)//68 d /right 262
		return true;
	return false;
}

