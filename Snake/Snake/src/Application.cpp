#include "Application.h"
#pragma region OpenGL libs
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#pragma endregion

#pragma region C++ libs
#include <iostream>
#pragma endregion

#pragma region Game dependency
#include "GlobalResouces.h"
#include "SnakeBody.h"
#include "GoalPoint.h"
#include "SnakeMovement.h"
#include "InputPlayer.h"
#pragma endregion

#pragma region Shaders Variables
const char* vertexShaderPath = "shader/vertex.shader";
const char* fragmentShaderPath = "shader/fragment.shader";
#pragma endregion

int numPointsGoalReached = 1;   

#pragma region  Draw Variables
float quadVertices[] = {
     0.5f,  0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f,
    -0.5f,  0.5f, 0.0f
};
unsigned int quadIndices[] = {
    0, 1, 3,
    1, 2, 3
};
unsigned int VBO, VAO, EBO;
#pragma endregion

#pragma region Game Components
SnakeBody snakeBody;
SnakeMovement snakeMovement = SnakeMovement(snakeBody.GetQuadsListRef());
GoalPoint goalPoint;
InputPlayer inputPlayer;
#pragma endregion 

int main()
{ 
    glm::mat4 projectionMatrix = glm::ortho(-halfWitdhWindow, halfWitdhWindow, -halfWitdhWindow, halfWitdhWindow, -1.0f, 1.0f);   
   
    goalPoint.SetPointGoalAtRandomPosition();
    
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow* window = glfwCreateWindow(scrWidth, scrHeight, "Snake", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    Shader shader(vertexShaderPath, fragmentShaderPath);
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(quadIndices), quadIndices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    while (!glfwWindowShouldClose(window))
    {
        ProcessPlayerInput(window);
        ProcessGameReset();
        ProcessDrawGame(shader, projectionMatrix, window);
        ProcessGameGoalReached();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}
void ProcessGameGoalReached()
{
    if (goalPoint.IsPointGoalReached(snakeBody.getSnakeHead().getPosition()))
    {
        std::cout << "PointsGoalReached : " << numPointsGoalReached << std::endl;
        numPointsGoalReached++;
        snakeMovement.OnPointGoalReached(numPointsGoalReached);
        goalPoint.SetPointGoalAtRandomPosition();
        snakeBody.AddQuadToSnakeBody();
    }
}
void ProcessPlayerInput(GLFWwindow* window)
{
    Direction newDir = inputPlayer.processInput(window);
    snakeMovement.SetSnakeDirection(newDir != None ? newDir : snakeMovement.GetSnakeDirection());
    snakeMovement.Move();
}
void ProcessDrawGame(Shader& shader, glm::mat4& projectionMatrix, GLFWwindow* window)
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    QuadTransformNode* current = snakeBody.GetQuadsList().getHead();
    while (current)
    {
        DrawQuad(shader, projectionMatrix, current->data);
        DrawQuad(shader, projectionMatrix, goalPoint.GetGoalPoint());

        current = current->next;
    }
    glfwSwapBuffers(window);
    glfwPollEvents();
}
void ProcessGameReset()
{
    if (snakeBody.IsHeadCollidingWithQuad() || snakeBody.IsSnakeOutsideWindow())
    {
        snakeBody.resetSnake();
        numPointsGoalReached = 1;
    }
}
void DrawQuad(Shader& shader, glm::mat4& projectionMatrix, QuadTransform quadData)
{
    unsigned int projectionMatrixLocation = glGetUniformLocation(shader.ID, "mvp");
    glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

    unsigned int transformLoc = glGetUniformLocation(shader.ID, "projection");

    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(quadData.getProjectionMatrix()));

    int vertexColorLocation = glGetUniformLocation(shader.ID, "quadColor");

    glUniform4f(vertexColorLocation,
        quadData.getColor().x,
        quadData.getColor().y,
        quadData.getColor().z,
        quadData.getColor().w);
    shader.use();
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
