cmake_minimum_required(VERSION 3.16)
project(BitucaZero LANGUAGES CXX)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(OpenCV REQUIRED COMPONENTS core highgui videoio)

add_library(camera_module
  src/camera/CameraManager.cpp
  src/camera/platform/linux/LaptopCameraLinux.cpp
  src/camera/platform/windows/LaptopCameraWindows.cpp
)

target_include_directories(camera_module PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/src/camera
  ${OpenCV_INCLUDE_DIRS}
)
target_link_libraries(camera_module PUBLIC ${OpenCV_LIBS})
target_compile_features(camera_module PUBLIC cxx_std_17)

if(WIN32)
  set(WINDOW_PLATFORM_SOURCE src/window/platform/windows/WindowsWindow.cpp)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
  find_package(X11 REQUIRED)
  set(WINDOW_PLATFORM_SOURCE src/window/platform/linux/LinuxWindow.cpp)
else()
  message(FATAL_ERROR "Window module supports Linux and Windows only")
endif()

add_library(window_module
  src/window/WindowManager.cpp
  ${WINDOW_PLATFORM_SOURCE}
)
target_include_directories(window_module PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/src/window
  ${OpenCV_INCLUDE_DIRS}
)
target_link_libraries(window_module PUBLIC ${OpenCV_LIBS})
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
  target_link_libraries(window_module PUBLIC X11::X11)
endif()
target_compile_features(window_module PUBLIC cxx_std_17)

add_executable(camera_preview
  apps/camera_preview/CameraPreview.cpp
  apps/camera_preview/CameraPreviewMain.cpp
)
target_include_directories(camera_preview PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/apps/camera_preview
)
target_link_libraries(camera_preview PRIVATE camera_module window_module)
