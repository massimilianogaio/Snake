#pragma once
#include "QuadTransformNode.h"

class QuadTransformLinkedList {
private:
    QuadTransformNode* head;
    QuadTransformNode* lastNode;

public:
    QuadTransformLinkedList();

    void add(const QuadTransform& transform);
    void display();
    void resetLength();
    QuadTransformNode* getHead();
    QuadTransformNode* getLastNode();
};
