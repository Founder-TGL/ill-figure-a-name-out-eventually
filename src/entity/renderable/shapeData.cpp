#include "shapeData.h"
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <vector>
#include <algorithm>


GLfloat pyramidVertices[] = {
    -0.5f, 0.0f,  0.5f,  0.83f, 0.70f, 0.44f,
    -0.5f, 0.0f, -0.5f,  0.83f, 0.70f, 0.44f,
     0.5f, 0.0f, -0.5f,  0.83f, 0.70f, 0.44f,
     0.5f, 0.0f,  0.5f,  0.83f, 0.70f, 0.44f,
     0.0f, 0.8f,  0.0f,  0.92f, 0.86f, 0.76f
};

GLuint pyramidIndices[] = {
    0, 1, 2,
    0, 2, 3,
    0, 1, 4,
    1, 2, 4,
    2, 3, 4,
    3, 0, 4
};

const int pyramidVerticesSize = sizeof(pyramidVertices);
const int pyramidIndicesSize = sizeof(pyramidIndices);

GLfloat cubeVertices[] = {
        // positions         // colors
    -0.5f,  0.0f, -0.5f,  0.6f, 0.3f, 0.2f,
     0.5f,  0.0f, -0.5f,  0.6f, 0.3f, 0.2f,
     0.5f,  1.0f, -0.5f,  0.6f, 0.3f, 0.2f,
    -0.5f,  1.0f, -0.5f,  0.6f, 0.3f, 0.2f,
    -0.5f,  0.0f,  0.5f,  0.6f, 0.3f, 0.2f,
     0.5f,  0.0f,  0.5f,  0.6f, 0.3f, 0.2f,
     0.5f,  1.0f,  0.5f,  0.6f, 0.3f, 0.2f,
    -0.5f,  1.0f,  0.5f,  0.6f, 0.3f, 0.2f

};
GLuint cubeIndices[] = {
    // back face
    0, 1, 2,
    2, 3, 0,
    // front face
    4, 5, 6,
    6, 7, 4,
    // left face
    4, 0, 3,
    3, 7, 4,
    // right face
    1, 5, 6,
    6, 2, 1,
    // top face
    3, 2, 6,
    6, 7, 3,
    // bottom face
    4, 5, 1,
    1, 0, 4

};
const int cubeVerticesSize = sizeof(cubeVertices);
const int cubeIndicesSize = sizeof(cubeIndices);

GLfloat sphereVertices[] = {
    // positions           // colors
     0.0f,  1.0f,  0.0f,   0.8f, 0.5f, 0.2f,
     0.894f,  0.447f,  0.0f,   0.8f, 0.5f, 0.2f,
     0.276f,  0.447f,  0.851f,   0.8f, 0.5f, 0.2f,
    -0.724f,  0.447f,  0.526f,   0.8f, 0.5f, 0.2f,
    -0.724f,  0.447f, -0.526f,   0.8f, 0.5f, 0.2f,
     0.276f,  0.447f, -0.851f,   0.8f, 0.5f, 0.2f,
     0.724f, -0.447f,  0.526f,   0.8f, 0.5f, 0.2f,
    -0.276f, -0.447f,  0.851f,   0.8f, 0.5f, 0.2f,
    -0.894f, -0.447f,  0.0f,     0.8f, 0.5f, 0.2f,
    -0.276f, -0.447f, -0.851f,   0.8f, 0.5f, 0.2f,
     0.724f, -0.447f, -0.526f,   0.8f, 0.5f, 0.2f,
     0.0f, -1.0f,  0.0f,         0.8f, 0.5f, 0.2f
};

GLuint sphereIndices[] = {
    0,1,2, 0,2,3, 0,3,4, 0,4,5, 0,5,1,
    1,6,2, 2,7,3, 3,8,4, 4,9,5, 5,10,1,
    6,7,2, 7,8,3, 8,9,4, 9,10,5, 10,6,1,
    6,11,7, 7,11,8, 8,11,9, 9,11,10, 10,11,6
};

const int sphereVerticesSize = sizeof(sphereVertices);
const int sphereIndicesSize = sizeof(sphereIndices);

