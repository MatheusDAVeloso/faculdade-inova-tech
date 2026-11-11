#ifndef CAMERA_PREVIEW_H
#define CAMERA_PREVIEW_H

#include "ICamera.h"
#include "IWindow.h"
#include "ICigaretteDetector.h"

/** Connects a camera source to a window without owning either one. */
class CameraPreview {
public:
  bool run(ICamera& camera, IWindow& window, ICigaretteDetector& detector);
};

#endif  // CAMERA_PREVIEW_H
