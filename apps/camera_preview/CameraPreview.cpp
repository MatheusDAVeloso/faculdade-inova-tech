#include "CameraPreview.h"

bool CameraPreview::run(ICamera& camera, IWindow& window) {
  if (!camera.openCamera()) {
    return false;
  }

  if (!window.openWindow("BitucaZero Camera Preview")) {
    camera.closeCamera();
    return false;
  }

  bool captureSucceeded = true;
  cv::Mat frame;
  while (true) {
    if (!camera.readFrame(frame)) {
      captureSucceeded = false;
      break;
    }

    if (window.shouldClose()) {
      break;
    }

    if (!window.showFrame(frame)) {
      captureSucceeded = false;
      break;
    }
  }

  window.closeWindow();
  camera.closeCamera();
  return captureSucceeded;
}
