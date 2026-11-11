#include "LinuxWindow.h"

#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include <cstdint>
#include <cstdlib>

struct LinuxWindow::Impl {
  Display* display = nullptr;
  ::Window window = 0;
  GC graphicsContext = nullptr;
  Atom deleteMessage = None;
  bool closeRequested = false;
  int width = 0;
  int height = 0;
};

namespace {

unsigned long channelToMask(std::uint8_t channel, unsigned long mask) {
  if (mask == 0) {
    return 0;
  }

  unsigned int shift = 0;
  while (((mask >> shift) & 1UL) == 0UL) {
    ++shift;
  }

  const unsigned long channelMask = mask >> shift;
  return ((static_cast<unsigned long>(channel) * channelMask / 255UL) << shift) &
         mask;
}

}  // namespace

LinuxWindow::LinuxWindow() : impl_(std::make_unique<Impl>()) {}

LinuxWindow::~LinuxWindow() {
  closeWindow();
}

bool LinuxWindow::openWindow(const std::string& title) {
  if (impl_->display != nullptr) {
    return true;
  }

  impl_->display = XOpenDisplay(nullptr);
  if (impl_->display == nullptr) {
    return false;
  }

  const int screen = DefaultScreen(impl_->display);
  impl_->window = XCreateSimpleWindow(
      impl_->display, RootWindow(impl_->display, screen), 0, 0, 640, 480, 1,
      BlackPixel(impl_->display, screen), WhitePixel(impl_->display, screen));
  if (impl_->window == 0) {
    closeWindow();
    return false;
  }

  XStoreName(impl_->display, impl_->window, title.c_str());
  XSelectInput(impl_->display, impl_->window, ExposureMask | StructureNotifyMask);

  impl_->deleteMessage = XInternAtom(impl_->display, "WM_DELETE_WINDOW", False);
  if (!XSetWMProtocols(impl_->display, impl_->window, &impl_->deleteMessage, 1)) {
    closeWindow();
    return false;
  }

  impl_->graphicsContext = XCreateGC(impl_->display, impl_->window, 0, nullptr);
  if (impl_->graphicsContext == nullptr) {
    closeWindow();
    return false;
  }

  XMapWindow(impl_->display, impl_->window);
  XFlush(impl_->display);
  return true;
}

bool LinuxWindow::showFrame(const cv::Mat& frame) {
  if (impl_->display == nullptr || frame.empty() || frame.depth() != CV_8U ||
      (frame.channels() != 1 && frame.channels() != 3 && frame.channels() != 4)) {
    return false;
  }

  const int screen = DefaultScreen(impl_->display);
  Visual* visual = DefaultVisual(impl_->display, screen);
  XImage* image = XCreateImage(impl_->display, visual,
                               static_cast<unsigned int>(DefaultDepth(impl_->display, screen)),
                               ZPixmap, 0, nullptr, frame.cols, frame.rows, 32, 0);
  if (image == nullptr) {
    return false;
  }

  image->data = static_cast<char*>(
      std::calloc(static_cast<std::size_t>(image->bytes_per_line),
                  static_cast<std::size_t>(image->height)));
  if (image->data == nullptr) {
    XDestroyImage(image);
    return false;
  }

  const int channels = frame.channels();
  for (int y = 0; y < frame.rows; ++y) {
    const std::uint8_t* row = frame.ptr<std::uint8_t>(y);
    for (int x = 0; x < frame.cols; ++x) {
      const std::uint8_t* source = row + x * channels;
      const std::uint8_t blue = source[0];
      const std::uint8_t green = channels == 1 ? blue : source[1];
      const std::uint8_t red = channels == 1 ? blue : source[2];
      const unsigned long pixel = channelToMask(red, visual->red_mask) |
                                  channelToMask(green, visual->green_mask) |
                                  channelToMask(blue, visual->blue_mask);
      XPutPixel(image, x, y, pixel);
    }
  }

  if (impl_->width != frame.cols || impl_->height != frame.rows) {
    XResizeWindow(impl_->display, impl_->window, frame.cols, frame.rows);
    impl_->width = frame.cols;
    impl_->height = frame.rows;
  }

  XPutImage(impl_->display, impl_->window, impl_->graphicsContext, image, 0, 0,
            0, 0, frame.cols, frame.rows);
  XFlush(impl_->display);
  XDestroyImage(image);
  return true;
}

bool LinuxWindow::shouldClose() {
  if (impl_->display == nullptr || impl_->closeRequested) {
    return true;
  }

  while (XPending(impl_->display) > 0) {
    XEvent event;
    XNextEvent(impl_->display, &event);

    if (event.type == ClientMessage &&
        static_cast<Atom>(event.xclient.data.l[0]) == impl_->deleteMessage) {
      impl_->closeRequested = true;
      break;
    }

    if (event.type == DestroyNotify && event.xdestroywindow.window == impl_->window) {
      impl_->closeRequested = true;
      break;
    }
  }

  return impl_->closeRequested;
}

void LinuxWindow::closeWindow() {
  if (impl_->display == nullptr) {
    return;
  }

  if (impl_->graphicsContext != nullptr) {
    XFreeGC(impl_->display, impl_->graphicsContext);
    impl_->graphicsContext = nullptr;
  }
  if (impl_->window != 0) {
    XDestroyWindow(impl_->display, impl_->window);
    impl_->window = 0;
  }
  XCloseDisplay(impl_->display);
  impl_->display = nullptr;
}
