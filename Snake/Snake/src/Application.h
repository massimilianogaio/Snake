#pragma once
#include "../shader/Shader.h"
#include "QuadTransform.h"
#include <GLFW/glfw3.h>


int main();
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void ProcessGameGoalReached();
void ProcessPlayerInput(GLFWwindow* window);
void ProcessDrawGame(Shader& shader, glm::mat4& projectionMatrix);
void ProcessGameReset();
void DrawQuad(Shader& shader, glm::mat4& projectionMatrix, QuadTransform quadData);
