#include "SnakeBody.h"
#include <iostream>
using namespace glm;

SnakeBody::SnakeBody()
{
    CreateSnakeQuad(startPosition, glm::vec3(0.0, 0.0, 1.0), glm::vec3(1.0f), glm::vec4(1.0f));
}

bool SnakeBody::IsHeadCollidingWithQuad()
{
    bool collision = false;
    QuadTransformNode* current = quadsList.getHead();
    while (current)
    {
        if (current != quadsList.getLastNode()
            && (&quadsList.getLastNode()->data)->getPosition() == current->data.getPosition())
        {
            collision = true;
        }
        current = current->next;
    }

    return collision;
}
void SnakeBody::CreateSnakeQuad(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, glm::vec4 color)
{
    QuadTransform newQuad = QuadTransform(position, rotation, scale, color);
    quadsList.add(newQuad);
}

QuadTransformLinkedList SnakeBody::GetQuadsList()
{
    return quadsList;
}
QuadTransformLinkedList* SnakeBody::GetQuadsListRef()
{
    return &quadsList;

}QuadTransform SnakeBody::getSnakeHead()
{
    return quadsList.getLastNode()->data;
}

void SnakeBody::resetSnake()
{
    quadsList.resetLength();
    quadsList.getHead()->data.setPosition(startPosition);
}

void SnakeBody::AddQuadToSnakeBody() {
    vec3 quadPos = quadsList.getHead()->data.getPreviousPosition();
    vec4 prevQuadCol = quadsList.getHead()->data.getColor();
    vec4 quadCol = prevQuadCol;
    quadCol.x = prevQuadCol.x > deltaColor ? prevQuadCol.x - deltaColor : 0.0f;
    quadCol.y = prevQuadCol.y > deltaColor ? prevQuadCol.y - deltaColor : 0.0f;
    quadCol.z = prevQuadCol.z > deltaColor ? prevQuadCol.z - deltaColor : 0.0f;

    CreateSnakeQuad(quadPos, vec3(0.0, 0.0, 1.0), vec3(1.0f), quadCol);
}


bool SnakeBody::IsSnakeOutsideWindow() {
    
    glm::vec3 currPos = quadsList.getLastNode()->data.getPosition();
    bool oustideX = currPos.x < -halfWitdhWindow || currPos.x > halfWitdhWindow;
    bool oustideY = currPos.y < -halfWitdhWindow || currPos.y > halfWitdhWindow;
    return oustideY || oustideX;
}

