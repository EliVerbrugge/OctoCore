cmake_minimum_required(VERSION 3.0.0)
project(octocomm VERSION 0.1.0)
set( CMAKE_TOOLCHAIN_FILE "C:/vcpkg/scripts/buildsystems/vcpkg.cmake" )

set( OpenCV_DIR "C:/vcpkg/installed/x64-windows/share/opencv" )

find_package( OpenCV REQUIRED ) # locate OpenCV in system
include_directories( ${OpenCV_INCLUDE_DIRS} ) # provide library headers
add_executable(octocomm main.cpp src/octocomm.h src/windows/octocomm_win.cpp src/windows/octocomm_win.h)
target_link_libraries( octocomm ${OpenCV_LIBS})