#pragma once

#include <glm/glm.hpp>
using namespace glm;
class QuadTransform {
    private:
        vec3 position;
        vec3 previousPosition;
        vec3 rotation;
        vec3 scale;
        vec4 color;

    public:
        QuadTransform(vec3 position, vec3 rotation, vec3 scale, vec4 color);

        vec3 getPosition() const;
        vec3 getPreviousPosition() const;
        void setPosition(const vec3& newPos);
        void addTranslation(const vec3& translation);
        vec3 getRotation() const;
        void setRotation(const vec3& newRot);
        vec3 getScale() const;
        void setScale(const vec3& newScale);
        vec4 getColor() const;
        void setColor(const vec4& newColor);
        mat4 getProjectionMatrix();
};