#pragma once
#include <glm/fwd.hpp>
#include <glm/gtc/type_ptr.hpp>

enum Direction {
    None,
    Up,
    Down,
    Left,
    Right
};
extern unsigned int scrWidth;
extern unsigned int scrHeight;
extern float halfWitdhWindow;
extern float deltaColor;
extern glm::vec3 startPosition;
extern float halfWitdhQuad;
