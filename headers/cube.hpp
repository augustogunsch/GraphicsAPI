#pragma once

#include <model.hpp>

class cube : virtual public model {
public:
    cube(program &program, camera& camera, glm::vec3 worldPosition, glm::vec3 rotation, 
    glm::vec3 scale);
    cube() = delete;
    void use();
    void render();
};