#include "Renderable.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>    
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include<glad/glad.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include "shaderClass.h"

Renderable::Renderable(float* vertices, size_t vertSize, GLuint* indices, size_t idxSize, glm::vec3 position, glm::vec3 orientation, glm::vec3 scale)
        : vbo(vertices, vertSize), ebo(indices, idxSize) , position(position), orientation(orientation), scale(scale)
    {
        std::vector<float> vec(vertices, vertices + (vertSize / sizeof(float)));
        std::vector<GLuint> ind(indices, indices + (idxSize / sizeof(GLuint)));
        this->vertices = std::move(vec);    
        this->indices = std::move(ind);
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

        
        model = glm::translate(model, position);

        // 3) build a "look‐at" quaternion turning +Z → forward
        glm::vec3 worldUp{0,1,0};
        glm::quat rot = glm::quatLookAt(glm::normalize(orientation), worldUp);
        model *= glm::toMat4(rot);


        model = glm::scale(model, scale);

        int modelLoc = glGetUniformLocation(shader.ID, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

        vao.Bind();
        glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
        vao.Unbind();
}