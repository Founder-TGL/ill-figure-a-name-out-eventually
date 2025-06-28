#include "player.h"
#include "Camera.h"
#include "Renderable.h"
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

Player::Player(int width, int height, Renderable playerMesh, float speed, int health, glm::vec3 position, float damageCooldown )
    : width(width), height(height), speed(speed), health(health), startingHealth(health), damageCooldownTime(damageCooldown), startPos(position) ,playerObj(std::move(playerMesh)), playerCamera(width, height, position + glm::vec3(0.0f, followHeight, followDist))
{
    playerObj.position = position;
    playerObj.orientation = glm::vec3(0.0f, 0.0f, 1.0f);

    playerObj.update();
    glm::vec3 viewDir = playerObj.position - playerCamera.position;
    playerCamera.orientation = glm::normalize(glm::vec3(viewDir.x, viewDir.y, 0.0f));
    moveCamera();
}

glm::vec3 Player::Input(float deltaTime, GLFWwindow* window) {
    // Mouse look
    if (mouseLocked) {
        double mouseX, mouseY;
        glfwGetCursorPos(window, &mouseX, &mouseY);

        float deltaX = float(mouseX - width / 2);
        float sensitivity = 0.15f;
        yaw -= deltaX * sensitivity;

        if (yaw > 360.f) yaw -= 360.f;
        if (yaw < 0.f) yaw += 360.f;

        playerObj.orientation = glm::normalize(glm::vec3(
            sin(glm::radians(yaw)),
            0.0f,
            cos(glm::radians(yaw))
        ));

        glfwSetCursorPos(window, width / 2, height / 2);
    }

    // Movement input
    glm::vec3 dir(0.0f);
    glm::vec3 forward = playerObj.orientation;
    glm::vec3 right = glm::normalize(glm::cross(forward, glm::vec3(0, 1, 0)));

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) dir += forward;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) dir -= forward;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) dir -= right;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) dir += right;

    // Camera update
    playerObj.update();
    moveCamera();

    // Mouse lock/unlock
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && !mouseLocked) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
        mouseLocked = true;
        glfwSetCursorPos(window, width / 2, height / 2);
    }

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        mouseLocked = false;
    }

    return (glm::length(dir) > 0.001f)
        ? speed * glm::normalize(dir) * deltaTime
        : glm::vec3(0.0f);
}

void Player::moveCamera() {
    // how far behind & how high above the player you want to be
    constexpr float followDist   = 5.0f;
    constexpr float followHeight = 2.0f;

    // 1) get the player’s flat forward direction
    glm::vec3 forward = playerObj.orientation;
    forward.y = 0.0f;
    forward = glm::normalize(forward);

    // 2) compute the desired camera position behind and above
    glm::vec3 camPos = playerObj.position
                     - forward * followDist      // behind
                     + glm::vec3(0.0f, followHeight, 0.0f); // up

    // 3) point camera at the player’s position
    glm::vec3 lookDir = playerObj.position - camPos;
    lookDir = glm::normalize(lookDir);

    // 4) write into your Camera
    playerCamera.position    = camPos;
    playerCamera.orientation = lookDir;
}