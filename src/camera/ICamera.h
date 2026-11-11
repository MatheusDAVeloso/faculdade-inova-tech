#ifndef I_CAMERA_H
#define I_CAMERA_H

#include <opencv2/core/mat.hpp>

/** Interface for opening and closing a camera device. */
class ICamera {
public:
  virtual ~ICamera() = default;

  /** Opens the camera. Returns true when it is ready to use. */
  virtual bool openCamera() = 0;

  /** Captures the next frame. Returns false when capture fails. */
  virtual bool readFrame(cv::Mat& frame) = 0;

  /** Releases the camera device. */
  virtual void closeCamera() = 0;
};

#endif  // I_CAMERA_H
