#include "player.h"
#include "Camera.h"
#include "Renderable.h"

Player::Player(int width, int height, Renderable playerMesh, glm::vec3 position)
    : width(width), height(height), playerMesh(playerMesh), playerCamera(width, height, position + cameraOffset)
{
    this->playerMesh.position = position;
    playerCamera.orientation = glm::normalize(playerMesh.position - playerCamera.position);
}

void Player::Inputs(GLFWwindow* window){
    glm::vec3& playerPosition = playerMesh.position;
    glm::vec3& cameraPosition = playerCamera.position;
    glm::vec3 playerOrientation = playerMesh.orientation;
    glm::vec3 cameraOrientation = playerCamera.orientation;
    glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);

    glm::vec3 direction(0.0f);




    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
        direction +=  playerOrientation;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
       direction -=  glm::normalize(glm::cross(playerOrientation, Up));

    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
        direction +=  playerOrientation;

    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
       direction -=  glm::normalize(glm::cross(playerOrientation, Up));
   
    }

    if (glm::length(direction) > 0.0f) {
    playerPosition += speed * glm::normalize(direction);
    moveCamera();
    std::cout << "player moved" << std::endl;
    }


    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
        if (firstClick)
        {
            mouseLocked = true;
        }
    }    
    
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        mouseLocked = false;
        firstClick = true;
    }
}

void Player::moveCamera()
{
    playerCamera.position = playerMesh.position + cameraOffset;
    playerCamera.orientation = glm::normalize(playerMesh.position - playerCamera.position);
}