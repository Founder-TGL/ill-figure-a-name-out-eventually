#ifndef HITBOX_H
#define HITBOX_H

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace Hitbox {

  // A 3D Oriented Bounding Box (world-space)
  struct OBB {
    glm::vec3 center;       // World-space center position
    glm::vec3 axes[3];      // World-space X, Y, Z unit vectors (local directions)
    glm::vec3 halfExtents;  // Half-size along each local axis

    // Create OBB from transformation
    void setFromTransform(
      const glm::vec3& position,
      const glm::quat& rotation,
      const glm::vec3& scale,
      const glm::vec3& localHalfExtents
    );
  };

  // Check if projections of A and B overlap along the given axis
  bool isOverlappingOnAxis(
    const OBB& a,
    const OBB& b,
    const glm::vec3& axis
  );

  // Run full Separating Axis Theorem test
  bool doOBBsIntersect(const OBB& a, const OBB& b);

} // namespace Hitbox

#endif
