#include "WindowManager.h"

#include <memory>

#if defined(__linux__)
#include "platform/linux/LinuxWindow.h"
#elif defined(_WIN32)
#include "platform/windows/WindowsWindow.h"
#endif

std::unique_ptr<IWindow> WindowManager::getWindow(WindowType type) {
  switch (type) {
#if defined(__linux__)
    case WindowType::Linux:
      return std::make_unique<LinuxWindow>();
#elif defined(_WIN32)
    case WindowType::Windows:
      return std::make_unique<WindowsWindow>();
#endif
    default:
      return nullptr;
  }
}
