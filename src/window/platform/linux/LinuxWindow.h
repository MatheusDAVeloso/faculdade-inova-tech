#ifndef LINUX_WINDOW_H
#define LINUX_WINDOW_H

#include <memory>
#include <string>

#include "IWindow.h"

class LinuxWindow : public IWindow {
public:
  LinuxWindow();
  ~LinuxWindow() override;

  bool openWindow(const std::string& title) override;
  bool showFrame(const cv::Mat& frame) override;
  bool shouldClose() override;
  void closeWindow() override;

private:
  struct Impl;
  std::unique_ptr<Impl> impl_;
};

#endif  // LINUX_WINDOW_H
