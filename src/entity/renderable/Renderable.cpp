#include "Renderable.h"
#include <iostream>
#include<glad/glad.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include "shaderClass.h"

Renderable::Renderable(float* vertices, size_t vertSize, GLuint* indices, size_t idxSize, glm::vec3 position, glm::vec3 orientation)
        : vbo(vertices, vertSize), ebo(indices, idxSize) , position(position), orientation(orientation)
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
 void Renderable::Draw(Shader& shader) {
        glm::mat4 model = glm::mat4(1.0f);

        // model = glm::rotate(model, orientation.x, glm::vec3(1.0f, 0.0f, 0.0f)); // pitch
        // model = glm::rotate(model, orientation.y, glm::vec3(0.0f, 1.0f, 0.0f)); // yaw
        // model = glm::rotate(model, orientation.z, glm::vec3(0.0f, 0.0f, 1.0f)); // roll

        model = glm::translate(model, position);


        int modelLoc = glGetUniformLocation(shader.ID, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

        vao.Bind();
        glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
        vao.Unbind();
}