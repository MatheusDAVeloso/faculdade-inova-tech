#include "CameraManager.h"

#include <exception>
#include <memory>
#include <utility>

#include "platform/linux/LaptopCameraLinux.h"
#include "platform/windows/LaptopCameraWindows.h"

std::unique_ptr<ICamera> CameraManager::getCamera(CameraType type) {
  std::unique_ptr<ICamera> camera;
  switch (type) {
    case CameraType::LaptopLinux:
      camera = std::make_unique<LaptopCameraLinux>();
      break;
    case CameraType::LaptopWindows:
      camera = std::make_unique<LaptopCameraWindows>();
      break;
    default:
      return nullptr;
  }

  try {
    if (!camera->openCamera()) {
      return nullptr;
    }
  } catch (const std::exception&) {
    return nullptr;
  }

  return camera;
}
