#ifndef PLAYER_H
#define PLAYER_H

#include "Camera.h"
#include "Renderable.h"
#include "gameObject.h"

class Player
{
    public:
        int width;
        int height;
        float speed;
        glm::vec3 cameraOffset = glm::vec3(0.0f, 2.0f, -6.0f);
        GameObject playerObj;
        Camera playerCamera;
        bool firstClick = true;
        bool mouseLocked = false;
        int health;
        float damageCooldown;
        float damageCooldownTime;
        glm::vec3 startPos = glm::vec3(0.0f, 0.0f, 0.0f);
        int startingHealth;

        Player(int width, int height, Renderable playerMesh, float speed = 0.1f, int health = 10, glm::vec3 position = {1.0f, 1.0f, 1.0f}, float damageCooldown = 0.5f);

        glm::vec3 pollMovementInput(GLFWwindow* window);
        void moveCamera();
        bool isDead() const { return health <= 0; }

};

#endif