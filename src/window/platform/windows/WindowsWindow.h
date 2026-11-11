#ifndef WINDOWS_WINDOW_H
#define WINDOWS_WINDOW_H

#include <string>

#include "IWindow.h"

class WindowsWindow : public IWindow {
public:
  WindowsWindow();
  ~WindowsWindow() override;

  bool openWindow(const std::string& title) override;
  bool showFrame(const cv::Mat& frame) override;
  bool shouldClose() override;
  void closeWindow() override;

private:
  std::string title_;
  bool isOpen_;
  bool wasVisible_;
};

#endif  // WINDOWS_WINDOW_H
