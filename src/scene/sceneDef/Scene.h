#ifndef SCENE_H
#define SCENE_H

#include "player.h"
#include "GameObject.h"
#include <vector>

class Scene {
public:
    Player* player = nullptr;
    std::vector<GameObject*> gameObjects;

    

    void setPlayer(Player* p) { player = p; }
    void addObject(GameObject* obj) { gameObjects.push_back(obj); }

    void update(GLFWwindow* window); // handles logic & collision
    void attemptMovePlayer(glm::vec3 proposedMove);
    void draw(Shader& shader);
};


#endif