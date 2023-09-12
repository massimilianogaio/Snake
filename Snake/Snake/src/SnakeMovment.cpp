#include "SnakeMovement.h"
#include <iostream>
using namespace glm;

SnakeMovement::SnakeMovement(QuadTransformLinkedList* snakeBody)
{
    this->snakeBody = snakeBody;
    incomatibleDirections[Up] = Down;
    incomatibleDirections[Right] = Left;
    incomatibleDirections[Left] = Right;
    incomatibleDirections[Down] = Up;
}

void SnakeMovement::Move()
{
    framePassed++;
    if (direction != None && framePassed >= deltaFrameMovement)
    {
        framePassed = 0;
        MoveSnakeTorwardDirection();
    }
}
void SnakeMovement::MoveSnakeTorwardDirection()
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

    QuadTransformNode* current = snakeBody->getHead();

    while (current->next != nullptr) {
        current->data.setPosition(current->next->data.getPosition());
        current = current->next;
    }

    current->data.addTranslation(translation);

}

void SnakeMovement::SetSnakeDirection(Direction direction)
{
    if (!IsDirectionAllowed(direction)) return;

    this->direction = direction;
}
void SnakeMovement::OnPointGoalReached(float numPointGoalReached)
{
    deltaFrameMovement -= (numPointGoalReached * 1.5f);
}

Direction SnakeMovement::GetSnakeDirection()
{
    return direction;
}

bool SnakeMovement::IsDirectionAllowed(Direction newDirection)
{
    return newDirection != incomatibleDirections[direction];
}
