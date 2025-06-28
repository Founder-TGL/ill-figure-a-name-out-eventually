#include "player.h"
#include "Camera.h"
#include "Renderable.h"
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

Player::Player(int width, int height, Renderable playerMesh, float speed, int health, glm::vec3 position, float damageCooldown )
    : width(width), height(height), speed(speed), health(health), startingHealth(health), damageCooldownTime(damageCooldown), startPos(position) ,playerObj(std::move(playerMesh)), playerCamera(width, height, position + cameraOffset)
{
    playerObj.position = position;
    playerObj.orientation = glm::vec3(0.0f, 0.0f, 1.0f);

    playerObj.update();
    glm::vec3 viewDir = playerObj.position - playerCamera.position;
    playerCamera.orientation = glm::normalize(glm::vec3(viewDir.x, viewDir.y, 0.0f));
    moveCamera();
}

glm::vec3 Player::pollMovementInput(GLFWwindow* window) {
    glm::vec3 dir(0.0f);
    glm::vec3 forward = playerObj.orientation;
    glm::vec3 right   = glm::normalize(glm::cross(forward, glm::vec3(0, 1, 0)));

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) dir += forward;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) dir -= forward;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) dir -= right;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) dir += right;

    return dir;
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