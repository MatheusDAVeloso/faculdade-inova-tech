#ifndef CAMERA_MANAGER_H
#define CAMERA_MANAGER_H

#include <memory>

#include "CameraType.h"
#include "ICamera.h"

/** Creates and validates a camera implementation for the current platform. */
class CameraManager {
public:
  /** Returns an opened camera owned by the caller, or nullptr on failure. */
  std::unique_ptr<ICamera> getCamera(CameraType type);
};

#endif  // CAMERA_MANAGER_H
