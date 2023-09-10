#include "QuadTransformNode.cpp"
#include "QuadTransform.cpp"
#include <iostream>
#pragma once

class QuadTransformLinkedList {
private:
    QuadTransformNode* head;
public:
    QuadTransformLinkedList() : head(nullptr) {}

    void add(const QuadTransform& transform)
    {
        QuadTransformNode* newNode = new QuadTransformNode(transform);
        if (!head) {
            head = newNode;
        }
        else {
            QuadTransformNode* current = head;
            while (current->next) {
                current = current->next;
            }
            current->next = newNode;
        }
    }

    void display()
    {
        QuadTransformNode* current = head;
        while (current) {
            std::cout << "Position: " << current->data.getPosition().x << ", " << current->data.getPosition().y << ", " << current->data.getPosition().z << std::endl;
            current = current->next;
        }
    }

    // Clean up the linked list
    ~QuadTransformLinkedList()
    {
        while (head) {
            QuadTransformNode* temp = head;
            head = head->next;
            delete temp;
        }
    }
    QuadTransformNode* getHead()
    {
        return head;
    }
};