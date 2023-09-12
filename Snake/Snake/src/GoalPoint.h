#pragma once
#include "QuadTransform.h"
class GoalPoint {
	public:
		void SetPointGoalAtRandomPosition();
		bool IsPointGoalReached(glm::vec3 snakeHeadPosition);
		QuadTransform GetGoalPoint();

	private:
		int GetRandomNumber(int minRange, int maxRange);
		QuadTransform goalPoint = QuadTransform(glm::vec3(0, 0.0, 1.0), glm::vec3(0, 0.0, 1.0), glm::vec3(1.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));



};