#pragma once
#include "GlobalResouces.h"
#include <map>
#include "QuadTransformLinkedList.h"


class SnakeMovement {
public:
    SnakeMovement(QuadTransformLinkedList* snakeBody);
    
    void Move();
    void MoveSnakeTorwardDirection();
    void SetSnakeDirection(Direction direction);
    void OnPointGoalReached(float numPointGoalReached);
    void ResetMovement();
    Direction GetSnakeDirection();

private:
    QuadTransformLinkedList* snakeBody;
    int deltaFrameMovement = 100;
    double framePassed = 0.0;
    double lastFrame = 0.0;
    Direction direction = Up;
    std::map<Direction, Direction> incomatibleDirections;

    bool IsDirectionAllowed(Direction newDirection);
};
