#ifndef MOVING_OBJECT_H
#define MOVING_OBJECT_H

#include "gameObject.h"

class MovingObject : public GameObject {
public:
    glm::vec3 velocity;
    float lifetime = 0.0f;
    float age = 0.0f;

    MovingObject(Renderable mesh, glm::vec3 spawnPos, glm::vec3 vel, float life)
        : GameObject(std::move(mesh)), velocity(vel), lifetime(life)
    {
        position = spawnPos;
        GameObject::update();
    }

    bool update(float deltaTime) {
        age += deltaTime;
        if (age > lifetime) return false;

        position += velocity * deltaTime;
        GameObject::update(); // sync mesh + hitbox
        return true;
    }
};


#endif
