//
// Created by Vladimir Shubarin on 21.09.2020.
//

#ifndef CGLABS__SCREEN_HPP_
#define CGLABS__SCREEN_HPP_
#define GL_SILENCE_DEPRECATION
#include "../aixlog.hpp"
#include "lib2D.hpp"
#include <OpenGL/gl.h>
#include <glfw3.h>
#include <iostream>
#include <string>

class Screen {
 public:
  Screen() = default;
  static GLFWwindow *createWindow(vec2<int> position, vec2<int> size, const std::string &windowName = "") {
	if (glfwInit()) {
	  LOG(INFO)
		  << "Creating new window with name: " + windowName + " and size: " + std::to_string(size.a) + "x" + std::to_string(size.b) +
			  " px\n";
	  GLFWwindow *window = glfwCreateWindow(size.a, size.b, windowName.c_str(), nullptr, nullptr);
	  if (window == nullptr) {
		LOG(ERROR) << "Cannot create window!\n";
		throw std::runtime_error("Failed to create window!");
	  }
	  LOG(INFO) << "Window created successfully\n";
	  glfwSetWindowPos(window, position.a, position.b);
	  glfwMakeContextCurrent(window);
	  glfwSwapInterval(1);
	  glfwShowWindow(window);

	  // Disabling ability to resize window
	  int w, h;
	  glfwGetWindowSize(window, &w, &h);
	  glfwSetWindowSizeLimits(window, w, h, w, h);
	  LOG(DEBUG) << "Disabled ability to resize window\n";
	  return window;
	} else {
	  LOG(ERROR) << "GLFW was not initialised!\n";
	  throw std::runtime_error("Failed to init GLFW");
	}
  }
  static void clearScreen(vec3<unsigned short int> color = {0, 0, 0}) {
	glClearColor(color.a, color.b, color.c, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  }
  static vec2<int> getWindowSize(GLFWwindow *window) {
	vec2<int> windowSize{0, 0};
	glfwGetWindowSize(window, &windowSize.a, &windowSize.b);
	return windowSize;
  }
};

#endif //CGLABS__SCREEN_HPP_
