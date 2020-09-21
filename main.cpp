#include "Libs/vhundef/screen.hpp"
#include "Libs/aixlog.hpp"
#include "Libs/vhundef/keyboard_handler.hpp"
void renderScene() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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


  // Основной цикл GLUT
  glutMainLoop();
  LOG(INFO) << "Program quit\n";
  return 0;
}
