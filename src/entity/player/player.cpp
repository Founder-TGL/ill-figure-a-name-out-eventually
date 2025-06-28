#include "player.h"
#include "Camera.h"
#include "Renderable.h"
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

Player::Player(int width, int height, Renderable playerMesh, float speed, glm::vec3 position)
    : width(width), height(height), speed(speed), playerMesh(playerMesh),playerCamera(width, height, position + cameraOffset)
{
    this->playerMesh.position = position;
    playerMesh.position = position;
    playerMesh.orientation = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 viewDir = playerMesh.position - playerCamera.position;
    playerCamera.orientation = glm::normalize(glm::vec3(viewDir.x, viewDir.y, 0.0f));

}

void Player::Inputs(GLFWwindow* window)
{
    bool keyPressed = false;
    glm::vec3& playerPosition = playerMesh.position;
    glm::vec3& cameraPosition = playerCamera.position;
    glm::vec3 playerOrientation = playerMesh.orientation;
    glm::vec3 cameraOrientation = playerCamera.orientation;
    glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 direction(0.0f, 0.0f, 0.0f);
    // std::cout << "Camera Pos: " << glm::to_string(playerCamera.position)
    //       << " | Camera Dir: " << glm::to_string(playerCamera.orientation)
    //       << " | Player Pos: " << glm::to_string(playerMesh.position) << std::endl;
    //           std::cout << "Offset length: " << glm::length(cameraOffset) << std::endl;




    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
        direction +=  playerOrientation;
        keyPressed = true;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
       direction -=  glm::normalize(glm::cross(playerOrientation, Up));
        keyPressed = true;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
        direction -=  playerOrientation;
        keyPressed = true;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
       direction +=  glm::normalize(glm::cross(playerOrientation, Up));
    keyPressed = true;
    }

    if (keyPressed && glm::length(direction) > 0.001f) {
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

    // Recalculate view direction without tilt
    glm::vec3 viewDir = playerMesh.position - playerCamera.position;
    viewDir.y = 0.0f; // flatten tilt
    viewDir = glm::normalize(viewDir);

    playerCamera.orientation = viewDir;
 
    std::cout << "Cam Pos: " << glm::to_string(playerCamera.position) << "\n";
std::cout << "Orientation: " << glm::to_string(playerCamera.orientation) << "\n";
std::cout << "Up Vector: " << glm::to_string(playerCamera.Up) << "\n";
}