#ifndef RENDERABLE_H
#define RENDERABLE_H

#include<glad/glad.h>
#include<glm/glm.hpp>
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"
#include"shaderClass.h"

class Renderable {
public:
    VAO vao;
    VBO vbo;
    EBO ebo;
    GLsizei indexCount;
    glm::vec3 position;
    glm::vec3 orientation;

    Renderable(float* vertices, size_t vertSize, GLuint* indices, size_t idxSize, glm::vec3 position = {0.0f, 0.0f, 0.0f}, glm::vec3 orientation = {0.0f, 0.0f, 0.0f});

    void Draw(Shader& shader);
};

#endif