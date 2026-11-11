#ifndef LAPTOP_CAMERA_WINDOWS_H
#define LAPTOP_CAMERA_WINDOWS_H

#include <memory>

#include "../../ICamera.h"

namespace cv {
class VideoCapture;
}

class LaptopCameraWindows : public ICamera {
public:
  LaptopCameraWindows();
  ~LaptopCameraWindows() override;

  bool openCamera() override;
  bool readFrame(cv::Mat& frame) override;
  void closeCamera() override;

private:
  std::unique_ptr<cv::VideoCapture> capture_;
};

#endif  // LAPTOP_CAMERA_WINDOWS_H
