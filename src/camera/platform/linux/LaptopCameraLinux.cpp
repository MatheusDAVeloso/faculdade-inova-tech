#include "LaptopCameraLinux.h"

#include <opencv2/videoio.hpp>

LaptopCameraLinux::LaptopCameraLinux()
    : capture_(std::make_unique<cv::VideoCapture>()) {}

LaptopCameraLinux::~LaptopCameraLinux() {
  closeCamera();
}

bool LaptopCameraLinux::openCamera() {
  if (capture_->isOpened()) {
    return true;
  }

  return capture_->open(0, cv::CAP_V4L2) && capture_->isOpened();
}

bool LaptopCameraLinux::readFrame(cv::Mat& frame) {
  return capture_->isOpened() && capture_->read(frame) && !frame.empty();
}

void LaptopCameraLinux::closeCamera() {
  if (capture_->isOpened()) {
    capture_->release();
  }
}
