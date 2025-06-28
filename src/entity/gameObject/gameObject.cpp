#define GLM_ENABLE_EXPERIMENTAL

#include "GameObject.h"
#include <glm/gtc/matrix_transform.hpp>

GameObject::GameObject(Renderable m)
  : mesh(m)
{
  // 1) compute the model‐space half extents from the mesh
  computeLocalBounds();
    
  // 2) initialize hitbox now
  update();
}

void GameObject::computeLocalBounds() {
  // mimic Renderable::computeLocalBounds
  glm::vec3 minP(+FLT_MAX), maxP(-FLT_MAX);
  auto& verts = mesh.vertices; // assume you expose raw verts
  size_t vertCount = verts.size() / 6;  // 6 floats per vertex

  for (size_t i = 0; i < vertCount; ++i) {
    glm::vec3 v(
      verts[i*6+0], verts[i*6+1], verts[i*6+2]
    );
    minP = glm::min(minP, v);
    maxP = glm::max(maxP, v);
  }
  localHalfExtents = (maxP - minP) * 0.5f;
}

void GameObject::update() {
  // 1) update mesh’s own transform
  mesh.position = position;
  mesh.orientation = orientation;
  mesh.scale = scale;

  // 2) update the hitbox from the same transform + localHalfExtents
  obb.setFromTransform(position, orientation, scale, localHalfExtents);
}

void GameObject::Draw(Shader& shader) {
  mesh.Draw(shader);
}

bool GameObject::wouldCollide(const glm::vec3& newPos, const GameObject& other)
{
    Hitbox::OBB futureOBB;
    futureOBB.setFromTransform(newPos, orientation, scale, localHalfExtents);
    return Hitbox::doOBBsIntersect(futureOBB, other.getOBB());
}