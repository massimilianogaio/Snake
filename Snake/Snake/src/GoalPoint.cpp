#include "GoalPoint.h"
#include <random>
#include <iostream>
#include "GlobalResouces.h"

int GoalPoint::GetRandomNumber(int minRange, int maxRange)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(minRange, maxRange);
    int num = distr(gen);

    std::cout << "GetRandomNumber generated " << num << std::endl;
    return num;
}
void GoalPoint::SetPointGoalAtRandomPosition()
{
    glm::vec3 pointGoalPos = glm::vec3(
        GetRandomNumber(-halfWitdhWindow + 2, halfWitdhWindow - 2),
        GetRandomNumber(-halfWitdhWindow + 2, halfWitdhWindow - 2), 0.0f);
    goalPoint.setPosition(pointGoalPos);
}

bool GoalPoint::IsPointGoalReached(glm::vec3 snakeHeadPosition)
{
    return snakeHeadPosition == goalPoint.getPosition();
}

QuadTransform GoalPoint::GetGoalPoint()
{
    return goalPoint;
}
