#toolchain.cmake
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR arm)
# compiler tools
set(tools_rockchip830 "/home/li/arm-rockchip830-linux-uclibcgnueabihf/bin" CACHE PATH "Cmake install prefix")
# set(tools_rockchip830 "/opt/arm-rockchip830-linux-uclibcgnueabihf/bin" CACHE PATH "Cmake install prefix")
set(MY_CROSS_prefix "/arm-rockchip830-linux-uclibcgnueabihf-")
set(CMAKE_C_COMPILER ${tools_rockchip830}/${MY_CROSS_prefix}gcc)
set(CMAKE_CXX_COMPILER ${tools_rockchip830}/${MY_CROSS_prefix}g++)
# Specify the paths to custom static library  for the toolchain utilities
file(GLOB LIB_DIRS LIST_DIRECTORIES true "${CMAKE_CURRENT_SOURCE_DIR}/lib/*")
set(CMAKE_FIND_ROOT_PATH ${LIB_DIRS})
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)
