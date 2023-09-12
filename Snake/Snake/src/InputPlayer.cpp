#include "InputPlayer.h"

Direction InputPlayer::processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
    int upKeyState = glfwGetKey(window, GLFW_KEY_UP);
    int rightKeyState = glfwGetKey(window, GLFW_KEY_RIGHT);
    int leftKeyState = glfwGetKey(window, GLFW_KEY_LEFT);
    int dowKeyState = glfwGetKey(window, GLFW_KEY_DOWN);

    prevKeyPressed =
        upKeyState == GLFW_PRESS ? GLFW_KEY_UP :
        rightKeyState == GLFW_PRESS ? GLFW_KEY_RIGHT :
        leftKeyState == GLFW_PRESS ? GLFW_KEY_LEFT :
        dowKeyState == GLFW_PRESS ? GLFW_KEY_DOWN :
        prevKeyPressed;

    if (prevKeyPressed != -1 && !directionKeyPressed)
    {
        directionKeyPressed = true;


        return prevKeyPressed == GLFW_KEY_UP ? Up :
            prevKeyPressed == GLFW_KEY_RIGHT ? Right :
            prevKeyPressed == GLFW_KEY_LEFT ? Left :
            prevKeyPressed == GLFW_KEY_DOWN ? Down : None;

    }

    if (glfwGetKey(window, prevKeyPressed) == GLFW_RELEASE)
    {
        directionKeyPressed = false;
        prevKeyPressed = -1;
    }
    return None;
}