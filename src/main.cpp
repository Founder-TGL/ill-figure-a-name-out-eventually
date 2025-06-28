#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>
#include<iostream>
#include<glad/glad.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<GLFW/glfw3.h>
#include<filesystem>
#include"shaderClass.h"
#include "shapeData.h"
#include "Camera.h"
#include "Renderable.h"
#include "player.h"
#include "Scene.h"

#include <math.h>

const static int width = 1600;
const static int height = 1000;

int main() {
    // --- Init GLFW + window ---
    if (!glfwInit()) return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window = glfwCreateWindow(width, height, "OpenGL Window", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create window\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    gladLoadGL();
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);
    glViewport(0, 0, width, height);
    glEnable(GL_DEPTH_TEST);

    // --- Shader ---
    Shader shaderProgram("entity/shaders/default.vert", "entity/shaders/default.frag");

    // --- Scene setup ---
    Scene scene;
    Renderable pyramid(pyramidVertices, pyramidVerticesSize, pyramidIndices, pyramidIndicesSize);
    Renderable cube(cubeVertices, cubeVerticesSize, cubeIndices, cubeIndicesSize);
	Renderable sphereMesh(sphereVertices, sphereVerticesSize, sphereIndices, sphereIndicesSize);
    Player* player = new Player(width, height, pyramid, 5.0f, 10, glm::vec3(0, 0, -2), 1.0f);
    GameObject* cubeObj = new GameObject(cube);
    cubeObj->setPosition(glm::vec3(1.5f, 0.0f, -2.0f));
    cubeObj->update();

    scene.setPlayer(player);
    scene.addObject(cubeObj);

    // --- Main loop ---
    float lastTime = glfwGetTime();
    while (!glfwWindowShouldClose(window)) {
        float currentTime = glfwGetTime();
        float deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        // Input
        // player->Inputs(window);
        if (player->mouseLocked) {
            double mx, my;
            glfwGetCursorPos(window, &mx, &my);
            if (abs(mx - width / 2) > 50 || abs(my - height / 2) > 50)
                glfwSetCursorPos(window, width / 2, height / 2);
        }

        // Update
        scene.update(deltaTime, window);

        // Render
        if (scene.isPlayerDead)
            glClearColor(0.4f, 0.0f, 0.0f, 1.0f); // blood red
        else
            glClearColor(0.0f, 0.0f, 0.01f, 1.0f); // normal background
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        shaderProgram.Activate();
        player->playerCamera.Matrix(45.0f, 0.1f, 1000.0f, shaderProgram, "camMatrix");
        scene.draw(shaderProgram);

        // Swap + poll
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Cleanup
    delete cubeObj;
    delete player;
    shaderProgram.Delete();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

