//
// Created by Vladimir Shubarin on 21.09.2020.
//

#ifndef CGLABS__SCREEN_HPP_
#define CGLABS__SCREEN_HPP_
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <string>
#include "lib2D.hpp"

class Screen {
  bool initialised = false;
 public:
  [[maybe_unused]] Screen(int argc, char **argv) {
	// инициализация
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	initialised = true;
  }
  [[maybe_unused]] void createWindow(vec2<int> position, vec2<int> size, const std::string &windowName = "") const {
	if (!initialised) { throw std::runtime_error("Glut was not initialised"); }
	glutInitWindowPosition(position.a, position.b);
	glutInitWindowSize(size.a, size.b);
	glutCreateWindow(windowName.c_str());
  }
};

#endif //CGLABS__SCREEN_HPP_
