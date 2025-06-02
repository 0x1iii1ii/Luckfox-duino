cmake_minimum_required(VERSION 3.10)
# set toolchain for cross compile
set(CMAKE_TOOLCHAIN_FILE toolchain.cmake)
# Set the project name
project(Luckfox-duino)
# Set the C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)
## --- Automatic source and header collection ---
# Collect all .cpp and .c sources under src/ and lib/
file(GLOB_RECURSE SRC_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/*.c"
)

# Collect all headers under include/ and lib/ (for IDE visibility)
file(GLOB_RECURSE HEADER_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/*.hpp"
)

add_executable(${PROJECT_NAME}
        ${SRC_FILES}
        ${HEADER_FILES}
)
# Add the include directories to the executable
target_include_directories(${PROJECT_NAME} PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
        "${CMAKE_CURRENT_SOURCE_DIR}/lib"
)
# Copy the executable to the output folder
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_CURRENT_SOURCE_DIR}/cmake-build-debug/${PROJECT_NAME}
        ${CMAKE_CURRENT_SOURCE_DIR}/output)
