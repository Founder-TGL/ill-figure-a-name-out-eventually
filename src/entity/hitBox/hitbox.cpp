#define GLM_ENABLE_EXPERIMENTAL
#include "hitbox.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <cmath>

namespace Hitbox {

void OBB::setFromTransform(
  const glm::vec3& position,
  const glm::quat& rotation,
  const glm::vec3& scale,
  const glm::vec3& localHalfExtents
) {
  // Model matrix = Translate * Rotate * Scale
  glm::mat4 model = glm::translate(glm::mat4(1.0f), position)
                  * glm::toMat4(rotation)
                  * glm::scale(glm::mat4(1.0f), scale);

  // Extract world-space position (center)
  center = glm::vec3(model[3]);

  // Extract and normalize local axes in world space
  for (int i = 0; i < 3; ++i) {
    axes[i] = glm::normalize(glm::vec3(model[i]));
  }

  // Scale local half extents by the given world scale
  halfExtents = localHalfExtents * scale;
}

bool isOverlappingOnAxis(
  const OBB& a,
  const OBB& b,
  const glm::vec3& axis
) {
  // Avoid division by 0 for degenerate axes
  float lengthSquared = glm::dot(axis, axis);
  if (lengthSquared < 1e-8f) return true;

  glm::vec3 unitAxis = glm::normalize(axis);

  // Project each box onto the axis
  float projectionA = 0.0f;
  float projectionB = 0.0f;

  for (int i = 0; i < 3; ++i) {
    projectionA += a.halfExtents[i] * std::abs(glm::dot(a.axes[i], unitAxis));
    projectionB += b.halfExtents[i] * std::abs(glm::dot(b.axes[i], unitAxis));
  }

  // Distance between box centers along the axi+s
  float centerDistance = std::abs(glm::dot(b.center - a.center, unitAxis));

  // Check for overlap
  return centerDistance <= (projectionA + projectionB);
}

bool doOBBsIntersect(const OBB& a, const OBB& b) {
  // Test 3 axes from box A
  for (int i = 0; i < 3; ++i)
    if (!isOverlappingOnAxis(a, b, a.axes[i]))
      return false;

  // Test 3 axes from box B
  for (int i = 0; i < 3; ++i)
    if (!isOverlappingOnAxis(a, b, b.axes[i]))
      return false;

  // Test 9 cross-product axes (edge-edge)
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      glm::vec3 crossAxis = glm::cross(a.axes[i], b.axes[j]);
      if (!isOverlappingOnAxis(a, b, crossAxis))
        return false;
    }
  }

  // No separating axis found → intersection confirmed
  return true;
}

} // namespace Hitbox
