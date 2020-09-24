#include "include/vhundef/screen.hpp"
#include "include/aixlog.hpp"
#include "include//GLFW/glfw3.h"

void handleKeyboard(GLFWwindow *window, int key, int scancode, int action, int mods) {
  LOG(DEBUG) << "Keyboard callback \n";
  if ((key == GLFW_KEY_Q && action == GLFW_PRESS) && glfwGetKey(window, GLFW_KEY_LEFT_CONTROL)) {
	LOG(INFO) << "Got quit command, destroying window\n";
	glfwDestroyWindow(window);
	LOG(DEBUG) << "Quiting...\n";
	glfwTerminate();
	exit(0);
  }
}

void drawOnScreen() {
  drawLine({{-0.9, 0.9}, {-0.9, 0.5}}, {255, 0, 0});
  drawLine({{-0.9, 0.5}, {-0.7, 0.5}}, {255, 0, 0});
  drawLine({{-0.7, 0.5}, {-0.8, 0.6}}, {255, 0, 0});
  sleep(30);
}

int main(int argc, char *argv[]) {
  AixLog::Log::init<AixLog::SinkCout>(AixLog::Severity::trace);
  LOG(INFO) << "Hello, World!\n";
  GLFWwindow *window = Screen::createWindow({100, 100}, {640, 480}, "Test");
  vec2<int> windowSize = Screen::getWindowSize(window);
  glfwGetFramebufferSize(window, &windowSize.a, &windowSize.b);

  glfwSetKeyCallback(window, handleKeyboard);
  while (glfwWindowShouldClose(window) == GL_FALSE) {
	Screen::updateScreen(drawOnScreen, {255, 255, 255}, window, true);
  }
  glfwDestroyWindow(window);
  glfwTerminate();
  LOG(INFO) << "Program quit\n";
  return 0;
}

