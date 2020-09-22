cmake_minimum_required(VERSION 3.17)
project(cgLabs)

set(CMAKE_CXX_STANDARD 20)
find_package(OpenGL REQUIRED)
find_package(GLFW3 REQUIRED)
find_package(Freetype REQUIRED)
include_directories(include/GLFW)

include_directories(${OPENGL_INCLUDE_DIRS} ${GLFW_INCLUDE_DIRS} ${FREETYPE_INCLUDE_DIRS})
add_executable(cgLabs main.cpp include/vhundef/lib2D.hpp include/vhundef/screen.hpp include/vhundef/ui.hpp include/vhundef/text.hpp)
target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} glfw ${GLFW_LIBRARIES} ${FREETYPE_LIBRARIES})