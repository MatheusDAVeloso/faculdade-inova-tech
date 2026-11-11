#ifndef I_WINDOW_H
#define I_WINDOW_H

#include <string>

#include <opencv2/core/mat.hpp>

/** Interface for displaying frames in a user interface window. */
class IWindow {
public:
  virtual ~IWindow() = default;

  virtual bool openWindow(const std::string& title) = 0;
  virtual bool showFrame(const cv::Mat& frame) = 0;
  virtual bool shouldClose() = 0;
  virtual void closeWindow() = 0;
};

#endif  // I_WINDOW_H
