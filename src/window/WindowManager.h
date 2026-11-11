#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H

#include <memory>

#include "IWindow.h"
#include "WindowType.h"

class WindowManager {
public:
  /** Creates the requested platform window, owned by the caller. */
  std::unique_ptr<IWindow> getWindow(WindowType type);
};

#endif  // WINDOW_MANAGER_H
