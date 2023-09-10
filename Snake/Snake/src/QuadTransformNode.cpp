#include "QuadTransform.cpp"

class QuadTransformNode {
public:
    QuadTransform data;
    QuadTransformNode* next;

    QuadTransformNode(const QuadTransform& transform) : data(transform), next(nullptr) {}
};
