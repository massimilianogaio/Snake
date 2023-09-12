#include "QuadTransformLinkedList.h"
#include <iostream>

QuadTransformLinkedList::QuadTransformLinkedList() : head(nullptr), lastNode(nullptr) {}

void QuadTransformLinkedList::add(const QuadTransform& transform)
{
    QuadTransformNode* newNode = new QuadTransformNode(transform);
    newNode->next = head;
    head = newNode;

    if (!lastNode) {
        lastNode = newNode;
    }
}

void QuadTransformLinkedList::display()
{
    QuadTransformNode* current = head;
    while (current) {
        std::cout << "Position: " << current->data.getPosition().x << ", " << current->data.getPosition().y << ", " << current->data.getPosition().z << std::endl;
        current = current->next;
    }
}

void QuadTransformLinkedList::resetLength()
{
    QuadTransformNode* current = head;
    while (current) {
        QuadTransformNode* temp = current;
        current = current->next;
        if (temp != lastNode) {
            std::cout << "delete" << std::endl;
            delete temp;
        }
    }
    head = lastNode;
    head->next = nullptr;
}

QuadTransformNode* QuadTransformLinkedList::getHead()
{
    return head;
}

QuadTransformNode* QuadTransformLinkedList::getLastNode()
{
    return lastNode;
}
