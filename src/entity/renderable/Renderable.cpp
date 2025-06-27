#include "Renderable.h"
#include <iostream>

Renderable::Renderable(float* vertices, size_t vertSize, GLuint* indices, size_t idxSize)
        : vbo(vertices, vertSize), ebo(indices, idxSize) 
    {
        vao.Bind();
        ebo.Bind();
        vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0); // position
        vao.LinkAttrib(vbo, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float))); // normal/color
        vao.Unbind();
        vbo.Unbind();
        ebo.Unbind();
        indexCount = static_cast<GLsizei>(idxSize / sizeof(GLuint));
    }
 void Renderable::Draw() {
        vao.Bind();
        glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
        vao.Unbind();
    }