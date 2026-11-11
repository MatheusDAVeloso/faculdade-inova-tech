#include "LaptopCameraWindows.h"

#include <opencv2/videoio.hpp>

LaptopCameraWindows::LaptopCameraWindows()
    : capture_(std::make_unique<cv::VideoCapture>()) {}

LaptopCameraWindows::~LaptopCameraWindows() {
  closeCamera();
}

bool LaptopCameraWindows::openCamera() {
  if (capture_->isOpened()) {
    return true;
  }

  return capture_->open(0, cv::CAP_MSMF) && capture_->isOpened();
}

bool LaptopCameraWindows::readFrame(cv::Mat& frame) {
  return capture_->isOpened() && capture_->read(frame) && !frame.empty();
}

void LaptopCameraWindows::closeCamera() {
  if (capture_->isOpened()) {
    capture_->release();
  }
}
