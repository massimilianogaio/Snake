#include "QuadTransform.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

QuadTransform::QuadTransform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, glm::vec4 color)
{
    this->position = position;
    this->previousPosition = position;
    this->rotation = rotation;
    this->scale = scale;
    this->color = color;
}

glm::vec3 QuadTransform::getPosition() const
{
    return position;
}

glm::vec3 QuadTransform::getPreviousPosition() const
{
    return previousPosition;
}

void QuadTransform::setPosition(const glm::vec3& newPos)
{
    previousPosition = position;
    position = newPos;
}

void QuadTransform::addTranslation(const glm::vec3& translation)
{
    previousPosition = position;
    position = position + translation;
}

glm::vec3 QuadTransform::getRotation() const
{
    return rotation;
}

void QuadTransform::setRotation(const glm::vec3& newRot)
{
    rotation = newRot;
}

glm::vec3 QuadTransform::getScale() const
{
    return scale;
}

void QuadTransform::setScale(const glm::vec3& newScale)
{
    scale = newScale;
}

glm::vec4 QuadTransform::getColor() const
{
    return color;
}

void QuadTransform::setColor(const glm::vec4& newColor)
{
    color = newColor;
}

glm::mat4 QuadTransform::getProjectionMatrix()
{
    glm::mat4 trans = glm::mat4(1.0f);
    trans = glm::translate(trans, getPosition());
    trans = glm::rotate(trans, glm::radians(90.0f), getRotation());
    trans = glm::scale(trans, getScale());
    return trans;
}
