#include "player.h"
#include "Camera.h"
#include "Renderable.h"
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

Player::Player(int width, int height, Renderable playerMesh, float speed, glm::vec3 position)
    : width(width), height(height), speed(speed), playerObj(std::move(playerMesh)), playerCamera(width, height, position + cameraOffset)
{
    playerObj.position = position;
    playerObj.orientation = glm::vec3(0.0f, 0.0f, 1.0f);

    playerObj.update();
    glm::vec3 viewDir = playerObj.position - playerCamera.position;
    playerCamera.orientation = glm::normalize(glm::vec3(viewDir.x, viewDir.y, 0.0f));
    moveCamera();
}

void Player::Inputs(GLFWwindow* window)
{
    bool keyPressed = false;
    glm::vec3& playerPosition = playerObj.position;
    glm::vec3& cameraPosition = playerCamera.position;
    glm::vec3 playerOrientation = playerObj.orientation;
    glm::vec3 cameraOrientation = playerCamera.orientation;
    glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 direction(0.0f, 0.0f, 0.0f);




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
        playerObj.update();
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
        playerObj.update();
    }


}

void Player::moveCamera()
{
  // 1) fixed offset:
  playerCamera.position = playerObj.position + cameraOffset;

  // 2) forward flat:
  glm::vec3 forward = playerObj.position - playerCamera.position;
  forward.y = 0.0f;

  if (glm::length(forward) > 0.0001f)
    forward = glm::normalize(forward);
  else
    forward = glm::vec3(0.0f, 0.0f, -1.0f); // fallback forward

  // 3) no‐roll basis:
  glm::vec3 worldUp  = glm::vec3(0,1,0);
  glm::vec3 right    = glm::normalize(glm::cross(worldUp, forward));
  glm::vec3 cameraUp = glm::cross(forward, right);

  // 4) store for Matrix():
  playerCamera.orientation = forward;

 
}