#include <glm/glm.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#pragma once

class QuadTransform {
private:
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;
    glm::vec4 color;

public:
    QuadTransform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, glm::vec4 color)
    {
        this->position = position;
        this->rotation = rotation;
        this->scale = scale;
        this->color = color;
    }

    glm::vec3 getPosition() const { return position; }
    void setPosition(const glm::vec3& newPos) { position = newPos; }
    void addTranslation(const glm::vec3& translation) { position = position + translation; }
    glm::vec3 getRotation() const { return rotation; }
    void setRotation(const glm::vec3& newRot) { rotation = newRot; }

    glm::vec3 getScale() const { return scale; }
    void setScale(const glm::vec3& newScale) { scale = newScale; }

    glm::vec4 getColor() const { return color; }
    void setColor(const glm::vec4& newColor) { color = newColor; }

    glm::mat4 getProjectionMatrix()
    {
        glm::mat4 trans = glm::mat4(1.0f);
        trans = glm::translate(trans, getPosition());
        trans = glm::rotate(trans, glm::radians(90.0f), getRotation());
        trans = glm::scale(trans, getScale());
        return trans;
    }
};
