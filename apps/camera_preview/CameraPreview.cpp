#include "CameraPreview.h"

#include <algorithm>
#include <iostream>
#include <string>

#include <opencv2/imgproc.hpp>

bool CameraPreview::run(ICamera& camera, IWindow& window,
                        ICigaretteDetector& detector) {
  if (!camera.openCamera()) {
    return false;
  }

  if (!window.openWindow("BitucaZero Camera Preview")) {
    camera.closeCamera();
    return false;
  }

  bool captureSucceeded = true;
  bool detectionWasActive = false;
  cv::Mat frame;
  while (true) {
    if (!camera.readFrame(frame)) {
      captureSucceeded = false;
      break;
    }

    if (window.shouldClose()) {
      break;
    }

    const std::vector<Detection> detections = detector.detect(frame);
    for (const Detection& detection : detections) {
      cv::rectangle(frame, detection.bounds, cv::Scalar(255, 0, 0), 2);
      const std::string label =
          "Possible cigarette " + std::to_string(detection.score);
      const int textY = std::max(18, detection.bounds.y - 8);
      cv::putText(frame, label, cv::Point(detection.bounds.x, textY),
                  cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(255, 0, 0), 1);
    }

    const bool detectionIsActive = !detections.empty();
    if (detectionIsActive && !detectionWasActive) {
      std::cout << "Possible rolled paper detected (" << detections.size()
                << " candidate(s))." << std::endl;
    }
    detectionWasActive = detectionIsActive;

    if (!window.showFrame(frame)) {
      captureSucceeded = false;
      break;
    }
  }

  window.closeWindow();
  camera.closeCamera();
  return captureSucceeded;
}
