#ifndef SCENE_H
#define SCENE_H

#include "player.h"
#include "GameObject.h"
#include "MovingObject.h"
#include "shapeData.h"
#include <vector>

class Scene {
public:
    Player* player = nullptr;
    std::vector<GameObject*> gameObjects;
    std::vector<MovingObject*> movingObjects;
    bool playerDamagedLastFrame = false;
    float spawnCooldown = 0.0f;
    Renderable enemyMesh;
    bool isPlayerDead = false;

    Scene();

    void setPlayer(Player* p) { player = p;}
    void addObject(GameObject* obj) { gameObjects.push_back(obj); }

    void update(float deltaTime, GLFWwindow* window); // handles logic & collision
    void attemptMovePlayer(glm::vec3 proposedMove);
    void draw(Shader& shader);
    void spawnMovingTarget();

    void handlePlayerDeath();
};


#endif