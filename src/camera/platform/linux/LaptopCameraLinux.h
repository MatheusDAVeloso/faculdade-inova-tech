#ifndef LAPTOP_CAMERA_LINUX_H
#define LAPTOP_CAMERA_LINUX_H

#include <memory>

#include "../../ICamera.h"

namespace cv {
class VideoCapture;
}

class LaptopCameraLinux : public ICamera {
public:
  LaptopCameraLinux();
  ~LaptopCameraLinux() override;

  bool openCamera() override;
  bool readFrame(cv::Mat& frame) override;
  void closeCamera() override;

private:
  std::unique_ptr<cv::VideoCapture> capture_;
};

#endif  // LAPTOP_CAMERA_LINUX_H
