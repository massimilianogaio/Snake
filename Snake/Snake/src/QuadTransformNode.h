#pragma once
#include "QuadTransform.h"

class QuadTransformNode {
public:
    QuadTransform data;
    QuadTransformNode* next;

    QuadTransformNode(const QuadTransform& transform);
};