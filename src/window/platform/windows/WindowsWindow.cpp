#include "WindowsWindow.h"

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

WindowsWindow::WindowsWindow() : isOpen_(false), wasVisible_(false) {}

WindowsWindow::~WindowsWindow() {
  closeWindow();
}

bool WindowsWindow::openWindow(const std::string& title) {
  if (isOpen_) {
    return true;
  }

  title_ = title;
  wasVisible_ = false;
  try {
    cv::namedWindow(title_, cv::WINDOW_AUTOSIZE);
    isOpen_ = true;
    return true;
  } catch (const cv::Exception&) {
    return false;
  }
}

bool WindowsWindow::showFrame(const cv::Mat& frame) {
  if (!isOpen_ || frame.empty()) {
    return false;
  }

  try {
    cv::imshow(title_, frame);
    return true;
  } catch (const cv::Exception&) {
    return false;
  }
}

bool WindowsWindow::shouldClose() {
  if (!isOpen_) {
    return true;
  }

  try {
    cv::waitKey(1);
    const double visibility =
        cv::getWindowProperty(title_, cv::WND_PROP_VISIBLE);
    if (visibility > 0.0) {
      wasVisible_ = true;
      return false;
    }
    if (visibility == 0.0) {
      return true;
    }
    return wasVisible_;
  } catch (const cv::Exception&) {
    return wasVisible_;
  }
}

void WindowsWindow::closeWindow() {
  if (!isOpen_) {
    return;
  }

  try {
    cv::destroyWindow(title_);
  } catch (const cv::Exception&) {
  }
  isOpen_ = false;
  wasVisible_ = false;
}
