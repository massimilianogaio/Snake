#pragma once

#include "QuadTransformLinkedList.h"
#include "GlobalResouces.h"

class SnakeBody {
public:
    SnakeBody();

    bool IsHeadCollidingWithQuad();
    void AddQuadToSnakeBody();
    bool IsSnakeOutsideWindow();
    void CreateSnakeQuad(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, glm::vec4 color);
    QuadTransformLinkedList GetQuadsList();
    QuadTransform getSnakeHead();
    void resetSnake();

private:
    QuadTransformLinkedList quadsList;
};
