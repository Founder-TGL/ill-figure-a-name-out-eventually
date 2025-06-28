#include "Scene.h"
#include "Hitbox.h"
#include <iostream>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>


void Scene::update(GLFWwindow* window) {
    if (!player) return;

    // Update player movement (input handled externally)
    player->playerObj.update();

    glm::vec3 direction = player->pollMovementInput(window); 
    if (glm::length(direction) > 0.001f) {
    glm::vec3 moveVec = player->speed * glm::normalize(direction);
    attemptMovePlayer(moveVec);
    }
}


void Scene::attemptMovePlayer(glm::vec3 proposedMove) {
    glm::vec3 proposedPos = player->playerObj.position + proposedMove;

    // Simulate updated hitbox
    Hitbox::OBB trial;
    trial.setFromTransform(proposedPos,
                           player->playerObj.orientation,
                           player->playerObj.scale,
                           player->playerObj.localHalfExtents);

    // Check against all other objects
    for (GameObject* obj : gameObjects) {
        if (Hitbox::doOBBsIntersect(trial, obj->getOBB())) {
            std::cout << "🟥 Movement blocked by object at: " << glm::to_string(obj->position) << "\n";
            return;
        }
    }

    // No collisions commit
    player->playerObj.position = proposedPos;
    player->playerObj.update();
    player->moveCamera();
}


void Scene::draw(Shader& shader) {
    if (player)
        player->playerObj.Draw(shader);

    for (auto* obj : gameObjects)
        obj->Draw(shader);
}