cmake_minimum_required(VERSION 3.17)
project(cgLabs)

set(CMAKE_CXX_STANDARD 20)
find_package(OpenGL REQUIRED)
find_package(GLFW3 REQUIRED)
include_directories(Libs/GLFW)

include_directories(${OPENGL_INCLUDE_DIRS} ${GLFW_INCLUDE_DIRS})
add_executable(cgLabs main.cpp Libs/vhundef/lib2D.hpp Libs/vhundef/screen.hpp Libs/vhundef/keyboard_handler.hpp)
target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} glfw ${GLFW_LIBRARIES})