#pragma once
#include "Exports.h"
#include "Window.h"
#include<glm/glm.hpp>
#include<glm\gtc\matrix_transform.hpp>
class  ENGINEDLL_API Input
{
private:
	Window *win;
public:
	Input(Window *window);
	bool IsKeyPressed(int i);
	

};