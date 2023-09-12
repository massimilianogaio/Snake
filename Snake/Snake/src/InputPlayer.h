#pragma once
#include <GLFW/glfw3.h>
#include "GlobalResouces.h"

class InputPlayer {
	public:
		Direction processInput(GLFWwindow* window);

	private:
		int prevKeyPressed = -1;
		bool directionKeyPressed = false;
};
