#pragma once

#include <glm/glm.hpp>

class QuadTransform {
private:
    glm::vec3 position;
    glm::vec3 previousPosition;
    glm::vec3 rotation;
    glm::vec3 scale;
    glm::vec4 color;

public:
    QuadTransform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, glm::vec4 color);

    glm::vec3 getPosition() const;
    glm::vec3 getPreviousPosition() const;
    void setPosition(const glm::vec3& newPos);
    void addTranslation(const glm::vec3& translation);
    glm::vec3 getRotation() const;
    void setRotation(const glm::vec3& newRot);
    glm::vec3 getScale() const;
    void setScale(const glm::vec3& newScale);
    glm::vec4 getColor() const;
    void setColor(const glm::vec4& newColor);
    glm::mat4 getProjectionMatrix();
};