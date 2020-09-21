#include "Libs/vhundef/screen.hpp"
#include "Libs/aixlog.hpp"
#include "Libs/vhundef/keyboard_handler.hpp"

void handleKeyboard() {
  LOG(DEBUG) << "Checking keyboard state\n";
  if (keyStates['q'] && bIsCtrlPressed) {
	LOG(INFO) << "Got quit command, destroying window\n";
	glutDestroyWindow(glutGetWindow());
	if (glutGetWindow() == 0) {
	  LOG(DEBUG) << "Window was destroyed successfully\n";
	  LOG(DEBUG) << "Quiting...\n";
	  exit(0);
	}
	LOG(ERROR) << "Error occurred while destroying window!\n";
	throw std::runtime_error("Failed to close window!");
  }
}

void renderScene() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  handleKeyboard();
  glutSwapBuffers();
}

int main(int argc, char *argv[]) {
  keyStates = new bool[256];
  AixLog::Log::init<AixLog::SinkCout>(AixLog::Severity::trace);
  LOG(INFO) << "Hello, World!\n";
  Screen screen(argc, argv);
  screen.createWindow({100, 100}, {200, 200}, "Test");
  LOG(DEBUG) << "Window Created\n";
  // регистрация обратных вызовов
  glutDisplayFunc(renderScene);
  glutKeyboardFunc(onKeyPressed);
  glutKeyboardUpFunc(onKeyUp);
  glutIdleFunc(renderScene);


  // Основной цикл GLUT
  glutMainLoop();
  LOG(INFO) << "Program quit\n";
  return 0;
}

