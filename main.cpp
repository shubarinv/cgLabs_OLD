#include "Libs/vhundef/screen.hpp"
#include "Libs/aixlog.hpp"
#include "Libs/vhundef/keyboard_handler.hpp"

void handleKeyboard() {
  LOG(DEBUG) << "Checking keyboard state\n";
  if (keyStates['q'] && bIsCtrlPressed) {
	LOG(INFO) << "Got quit command, destroying window\n";
	LOG(DEBUG) << "Window was destroyed successfully\n";
	LOG(DEBUG) << "Quiting...\n";
	exit(0);
  }
  LOG(ERROR) << "Error occurred while destroying window!\n";
  throw std::runtime_error("Failed to close window!");
}

void renderScene() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  handleKeyboard();
}

int main(int argc, char *argv[]) {
  keyStates = new bool[256];
  AixLog::Log::init<AixLog::SinkCout>(AixLog::Severity::trace);
  LOG(INFO) << "Hello, World!\n";
  GLFWwindow *window = Screen::createWindow({100, 100}, {200, 200}, "Test");

  while (glfwWindowShouldClose(window) == GL_FALSE) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor4f(1, 0, 0, 1);
	drawCircle(0, 0, 0.5, 50, {255, 0, 0});

	glfwSwapBuffers(window);
	glfwPollEvents();
  }
  glfwDestroyWindow(window);
  glfwTerminate();
  LOG(INFO) << "Program quit\n";
  return 0;
}

