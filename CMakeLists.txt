cmake_minimum_required(VERSION 3.17)
project(cgLabs)

set(CMAKE_CXX_STANDARD 20)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLFW3 REQUIRED)
# Included these two lines:

include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS} ${GLFW_INCLUDE_DIRS})
add_executable(cgLabs main.cpp Libs/vhundef/lib2D.hpp Libs/vhundef/screen.hpp Libs/vhundef/keyboard_handler.hpp)
target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} ${GLFW_LIBRARIES})