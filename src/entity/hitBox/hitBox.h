#ifndef HITBOX_H
#define HITBOX_H

#include <glm/glm.hpp>

namespace Hitbox {

  // A 3D Oriented Bounding Box (world-space)
  struct OBB {
    glm::vec3 center;       // Center of the box in world space
    glm::vec3 axes[3];      // Local X, Y, Z axes in world space
    glm::vec3 halfExtents;  // Half-size along each axis

    // Set this OBB from position, Euler angles, scale, and local half-size
    void setFromTransform(
      const glm::vec3& position,
      const glm::vec3& eulerAngles,      // Rotation in radians
      const glm::vec3& scale,
      const glm::vec3& localHalfExtents
    );
  };

  // Projects both boxes onto the axis and checks 1D overlap
  bool isOverlappingOnAxis(
    const OBB& a,
    const OBB& b,
    const glm::vec3& axis
  );

  // Full SAT test between two OBBs
  bool doOBBsIntersect(const OBB& a, const OBB& b);

} // namespace Hitbox

#endif