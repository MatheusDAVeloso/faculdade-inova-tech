#include <iostream>
#include <memory>
#include <csignal>

#include "CameraManager.h"
#include "CameraPreview.h"
#include "CameraType.h"
#include "WindowManager.h"
#include "WindowType.h"

int main() {
#if defined(__linux__)
  const CameraType cameraType = CameraType::LaptopLinux;
#elif defined(_WIN32)
  const CameraType cameraType = CameraType::LaptopWindows;
#else
  std::cerr << "This camera preview supports Linux and Windows only.\n";
  return 1;
#endif

  CameraManager cameraManager;
  std::unique_ptr<ICamera> camera = cameraManager.getCamera(cameraType);
  if (!camera) {
    std::cerr << "Could not open the selected camera.\n";
    return 1;
  }

  WindowManager windowManager;
  const WindowType windowType =
#if defined(__linux__)
      WindowType::Linux;
#elif defined(_WIN32)
      WindowType::Windows;
#endif
  std::unique_ptr<IWindow> window = windowManager.getWindow(windowType);
  if (!window) {
    std::cerr << "Could not create the selected window.\n";
    return 1;
  }

  CameraPreview preview;
  if (!preview.run(*camera, *window)) {
    std::cerr << "Camera preview stopped because frame capture failed.\n";
    return 1;
  }

#if defined(__linux__)
  std::raise(SIGINT);
#endif

  return 0;
}
