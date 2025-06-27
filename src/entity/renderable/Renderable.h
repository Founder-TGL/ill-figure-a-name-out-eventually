#ifndef RENDERABLE_H
#define RENDERABLE_H

#include<glad/glad.h>
#include<glm/glm.hpp>
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"

class Renderable {
public:
    VAO vao;
    VBO vbo;
    EBO ebo;
    GLsizei indexCount;

    Renderable(float* vertices, size_t vertSize, GLuint* indices, size_t idxSize);

    void Draw();
};

#endif