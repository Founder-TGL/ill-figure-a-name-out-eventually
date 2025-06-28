#ifndef MOVING_OBJECT_H
#define MOVING_OBJECT_H

#include "gameObject.h"

class MovingObject : public GameObject {
public:
    glm::vec3 velocity;
    float lifetime = 0.0f;
    float age = 0.0f;
    int damage = 1;

    MovingObject(Renderable mesh, glm::vec3 spawnPos, glm::vec3 vel, float life);

    bool update(float deltaTime);
};


#endif
