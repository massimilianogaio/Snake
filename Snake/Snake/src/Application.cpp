#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include "../shader/Shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "QuadTransformLinkedList.cpp"
#include <map>
#include <random>

#pragma region  Window Variables
unsigned int scrWidth = 900;
unsigned int scrHeight = 900;
const char* title = "Snake";
#pragma endregion
#pragma region Shaders Variables
const char* vertexShaderPath = "shader/vertex.shader";
const char* fragmentShaderPath = "shader/fragment.shader";
#pragma endregion
#pragma region Time Variables
double framePassed = 0.0;
double lastFrame = 0.0;
const int frameRate = 200;
#pragma endregion   
enum Direction {
    None,
    Up,
    Down,
    Left,
    Right
};
float halfWitdhQuad = 1.0f;
float halfWitdhWindow = 25.0f;
std::map<Direction, Direction> incomatibleDirections;
Direction snakeDirection = Up;
int prevKeyPressed = -1;
bool directionKeyPressed = false;
QuadTransform pointGloal = QuadTransform(glm::vec3(0, 0.0, 1.0), glm::vec3(0, 0.0, 1.0), glm::vec3(1.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
QuadTransform* snakeHead;

float quadVertices[] = {
     0.5f,  0.5f, 0.0f,  // top right
     0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  // bottom left
    -0.5f,  0.5f, 0.0f   // top left 
};
unsigned int quadIndices[] = {
    0, 1, 3,   // first triangle
    1, 2, 3    // second triangle
};

QuadTransformLinkedList quadsList;
unsigned int VBO, VAO, EBO;

#pragma region  Function Declaration
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
int main();
void DrawQuad(Shader& shader, glm::mat4& projectionMatrix, QuadTransform quadData);
void processInput(GLFWwindow* window);
void CreateSnakeQuad(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, glm::vec4 color, bool isSnakeHead);
void MoveSnakeTorwardDirection(Direction direction);
int GetRandomNumber(int minRange, int maxRange);
void SetPointGoalRandomPosition();
bool IsPointGoalReached();
#pragma endregion

int main()
{
    glm::mat4 projectionMatrix = glm::ortho(-halfWitdhWindow, halfWitdhWindow, -halfWitdhWindow, halfWitdhWindow, -1.0f, 1.0f);

    incomatibleDirections[Up] = Down;
    incomatibleDirections[Right] = Left;
    incomatibleDirections[Left] = Right;
    incomatibleDirections[Down] = Up;
    
    CreateSnakeQuad(glm::vec3(0.0f, -2 * halfWitdhQuad, 0.0f), glm::vec3(0, 0.0, 1.0), glm::vec3(1.0f), glm::vec4(0.8f), false);
    CreateSnakeQuad(glm::vec3(0.0f, -1 * halfWitdhQuad, 0.0f), glm::vec3(0, 0.0, 1.0), glm::vec3(1.0f), glm::vec4(0.9f), false);
    CreateSnakeQuad(glm::vec3(0.0f,  0 * halfWitdhQuad, 0.0f), glm::vec3(0.0, 0.0, 1.0), glm::vec3(1.0f), glm::vec4(1.0f), true);
    
    SetPointGoalRandomPosition();
    
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow* window = glfwCreateWindow(scrWidth, scrHeight, title, NULL, NULL);
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
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(quadIndices), quadIndices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);

    while (!glfwWindowShouldClose(window))
    {
        framePassed ++;

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        processInput(window);

        
        QuadTransformNode* current = quadsList.getHead();
        while (current)
        {
            DrawQuad(shader, projectionMatrix, pointGloal);
            DrawQuad(shader, projectionMatrix, current->data);
            
            current = current->next;
        }
        if (snakeDirection != None && framePassed >= frameRate)
        {
            framePassed = 0;
            MoveSnakeTorwardDirection(snakeDirection);
        }
        
        if (IsPointGoalReached())
        {
            std::cout << "PointGoalReached" << std::endl;
            SetPointGoalRandomPosition();
        }
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
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
void processInput(GLFWwindow* window)
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


        Direction newSnakeDirection = prevKeyPressed == GLFW_KEY_UP ? Up :
            prevKeyPressed == GLFW_KEY_RIGHT ? Right :
            prevKeyPressed == GLFW_KEY_LEFT ? Left :
            prevKeyPressed == GLFW_KEY_DOWN ? Down: snakeDirection;

        if (newSnakeDirection == incomatibleDirections[snakeDirection])
        {
            std::cout << newSnakeDirection << "not allowed" << std::endl;
        }
        else
        {
            snakeDirection = newSnakeDirection;
        }
        
        std::cout << snakeDirection << std::endl;
    }

    if(glfwGetKey(window, prevKeyPressed) == GLFW_RELEASE)
    {
        directionKeyPressed = false;
        prevKeyPressed = -1;
    }
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
void CreateSnakeQuad(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, glm::vec4 color, bool isSnakeHead)
{
    QuadTransform newQuad = QuadTransform(position, rotation, scale, color);
    quadsList.add(newQuad);
    if (isSnakeHead)
    {
        snakeHead = &newQuad;
    }
}

void MoveSnakeTorwardDirection(Direction direction)
{
    glm::vec3 translation = glm::vec3(0.0f, 0.0f, 0.0);
    switch (direction)
    {
        case Up:
            translation = glm::vec3(0.0f, halfWitdhQuad, 0.0);
            break;
        case Down:
            translation = glm::vec3(0.0f, halfWitdhQuad * -1, 0.0);
            break;
        case Left:
            translation = glm::vec3(halfWitdhQuad * -1, 0.0f, 0.0);
            break;
        case Right:
            translation = glm::vec3(halfWitdhQuad, 0.0f, 0.0);
            break;
        default:
            break;
    }

    QuadTransformNode* current = quadsList.getHead();

    while (current->next != nullptr) {
        current->data.setPosition(current->next->data.getPosition());      
        current = current->next;
    }

    current->data.addTranslation(translation);

}


int GetRandomNumber(int minRange, int maxRange)
{
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<> distr(minRange, maxRange); // define the range
    int num = distr(gen);

    std::cout << "GetRandomNumber generated " << num << std::endl;
    return num;
}

void SetPointGoalRandomPosition()
{
    glm::vec3 pointGoalPos = glm::vec3(GetRandomNumber(-halfWitdhWindow, halfWitdhWindow), GetRandomNumber(-halfWitdhWindow, halfWitdhWindow), 0.0f);
    pointGloal.setPosition(pointGoalPos);
}

bool IsPointGoalReached()
{
    return (&quadsList.getLastNode()->data)->getPosition() == pointGloal.getPosition();
}
