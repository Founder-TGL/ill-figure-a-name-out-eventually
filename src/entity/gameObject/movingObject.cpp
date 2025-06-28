#include "movingObject.h"

MovingObject::MovingObject(Renderable mesh, glm::vec3 spawnPos, glm::vec3 vel, float life)
    : GameObject(std::move(mesh)), velocity(vel), lifetime(life)
{
    position = spawnPos;
    GameObject::update();
}

bool MovingObject::update(float deltaTime) {
    age += deltaTime;
    if (age > lifetime) return false;

    position += velocity * deltaTime;
    GameObject::update(); // sync mesh + hitbox
    return true;
}