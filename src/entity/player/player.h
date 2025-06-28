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

        Player(int width, int height, Renderable playerMesh, float speed = 0.1f, glm::vec3 position = {1.0f, 1.0f, 1.0f});

    glm::vec3 pollMovementInput(GLFWwindow* window);
    void moveCamera();
    private:

};

#endif