#ifndef RENDERABLE_H
#define RENDERABLE_H

#include<glad/glad.h>
#include<glm/glm.hpp>
#include"VAO.h"
#include"VBO.h"
#include<vector>
#include"EBO.h"
#include"shaderClass.h"

class Renderable {
public:
    VAO vao;
    VBO vbo;
    EBO ebo;
    GLsizei indexCount;
    std::vector<GLfloat> vertices;
    std::vector<GLuint> indices;
    glm::vec3 position;
    glm::vec3 orientation;
    glm::vec3 scale;

    Renderable(float* vertices, size_t vertSize, GLuint* indices, size_t idxSize, glm::vec3 position = {0.0f, 0.0f, 0.0f}, glm::vec3 orientation = {0.0f, 0.0f, 1.0f}, glm::vec3 scale = {1.0f, 1.0f, 1.0f});

    void Draw(Shader& shader);
};

#endif