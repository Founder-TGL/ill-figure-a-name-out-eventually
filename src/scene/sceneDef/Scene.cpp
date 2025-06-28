#include "Scene.h"
#include "Hitbox.h"
#include <iostream>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

Scene::Scene() : enemyMesh(Renderable(cubeVertices, cubeVerticesSize, cubeIndices, cubeIndicesSize)){}

void Scene::update(float deltaTime, GLFWwindow* window) {
    if (!player) return;

    if (player->isDead()) {
        isPlayerDead = true;
        handlePlayerDeath();
        std::cout << "restarting game...\n";
        return;
    }

    // Step cooldown
    player->damageCooldown -= deltaTime;
    player->damageCooldown = std::max(0.0f, player->damageCooldown);

    const auto& playerOBB = player->playerObj.getOBB();

    for (MovingObject* obj : movingObjects) {
        if (Hitbox::doOBBsIntersect(playerOBB, obj->getOBB()) && player->damageCooldown <= 0.0f) {
            player->health -= obj->damage;
            std::cout << "🔥 player hit for " << obj->damage << " hp\n";
            player->damageCooldown = player->damageCooldownTime;
            break;
        }
    }

    // Proposed move + attempt with collision
    glm::vec3 moveVec = player->Input(deltaTime, window);
    if (glm::length(moveVec) > 0.001f)
        attemptMovePlayer(moveVec);

    // Update enemies
    for (int i = movingObjects.size() - 1; i >= 0; --i) {
        if (!movingObjects[i]->update(deltaTime))
            movingObjects.erase(movingObjects.begin() + i);
    }

    // Spawn logic
    spawnCooldown -= deltaTime;
    if (spawnCooldown <= 0.0f) {
        spawnMovingTarget();
        spawnCooldown = 3.0f;
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
    
    for (MovingObject* obj : movingObjects) {
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
    for (auto& mob : movingObjects)
        mob->Draw(shader);
}

void Scene::spawnMovingTarget() {
    glm::vec3 spawnPos = player->playerObj.position + glm::vec3(rand()%100 - 50, 0, rand()%100 - 50);
    glm::vec3 toPlayer = glm::normalize(player->playerObj.position - spawnPos);
    float speed = 20.0f;
    float life = 8.0f;

    toPlayer *= speed;

    Renderable mobMesh = enemyMesh;
    mobMesh.scale = glm::vec3(0.5f);
    movingObjects.push_back(new MovingObject(enemyMesh, spawnPos, toPlayer, life));

}

void Scene::handlePlayerDeath(){
    player->playerObj.position = player->startPos;
    player->health = player->startingHealth;
    isPlayerDead = false;
}