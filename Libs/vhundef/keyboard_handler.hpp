//
// Created by Vladimir Shubarin on 21.09.2020.
//

#ifndef CGLABS_LIBS_VHUNDEF_KEYBOARD_HANDLER_HPP_
#define CGLABS_LIBS_VHUNDEF_KEYBOARD_HANDLER_HPP_

#include "../aixlog.hpp"
bool *keyStates;
bool bIsShiftPressed = false;
bool bIsCtrlPressed = false;
bool bIsAltPressed = false;
void onKeyPressed(unsigned char key, int x, int y) {
  if (!keyStates[key]) {
	LOG(INFO) << "Key: " + std::string(1, key) + " DOWN\n";
	keyStates[key] = true;
  }
  glutGetModifiers();
  bIsCtrlPressed = GLUT_ACTIVE_CTRL;
  bIsAltPressed = GLUT_ACTIVE_ALT;
  bIsShiftPressed = GLUT_ACTIVE_SHIFT;

}
void onKeyUp(unsigned char key, int x, int y) {
  LOG(INFO) << "Key: " + std::string(1, key) + " UP\n";
  keyStates[key] = false;
  glutGetModifiers();
}

#endif //CGLABS_LIBS_VHUNDEF_KEYBOARD_HANDLER_HPP_
