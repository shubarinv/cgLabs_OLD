cmake_minimum_required(VERSION 3.17)
project(cgLabs)

set(CMAKE_CXX_STANDARD 20)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLFW3 REQUIRED)

# Included these two lines:

include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS} ${GLFW_INCLUDE_DIRS})
add_executable(cgLabs main.cpp lib2D.hpp)
target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} ${GLFW_LIBRARIES})