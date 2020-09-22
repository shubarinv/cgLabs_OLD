#include "include/vhundef/screen.hpp"
#include "include/aixlog.hpp"
#include "include/vhundef/text.hpp"

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


int main(int argc, char *argv[]) {
  AixLog::Log::init<AixLog::SinkCout>(AixLog::Severity::trace);
  LOG(INFO) << "Hello, World!\n";
  GLFWwindow *window = Screen::createWindow({100, 100}, {200, 200}, "Test");
  Text text;
  vec2<int> windowSize = Screen::getWindowSize(window);
  glfwGetFramebufferSize(window, &windowSize.a, &windowSize.b);

  glfwSetKeyCallback(window, handleKeyboard);
  while (glfwWindowShouldClose(window) == GL_FALSE) {
	Screen::clearScreen({255, 255, 255});
	drawCircle(0, 0, 0.5, 50, {255, 0, 0});
	glfwSwapBuffers(window);
	glfwPollEvents();
  }
  glfwDestroyWindow(window);
  glfwTerminate();
  LOG(INFO) << "Program quit\n";
  return 0;
}

