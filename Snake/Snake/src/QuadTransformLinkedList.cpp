#include "QuadTransformNode.cpp"
#include "QuadTransform.cpp"
#include <iostream>
#pragma once

class QuadTransformLinkedList {
private:
    QuadTransformNode* head;
    QuadTransformNode* lastNode;
public:
    QuadTransformLinkedList() : head(nullptr) {}

    void add(const QuadTransform& transform)
    {
        QuadTransformNode* newNode = new QuadTransformNode(transform);
        newNode->next = head;
        head = newNode;

        if (!lastNode) {
            lastNode = newNode;
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


    void ResetSnakeLength()
    {
        
        QuadTransformNode* current = head;
        while (current) {
            QuadTransformNode* temp = current;
            std::cout << "Position: " << current->data.getPosition().x << ", " << current->data.getPosition().y << ", " << current->data.getPosition().z << std::endl;

            current = current->next;
            if (temp != lastNode)
            {
                std::cout << "delete" << std::endl;
                delete temp;
            }
        }
        head = lastNode;
        head->next = nullptr;
    }

    QuadTransformNode* getHead()
    {
        return head;
    }
    QuadTransformNode* getLastNode()
    {
        return lastNode;
    }
};