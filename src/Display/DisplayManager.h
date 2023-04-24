#ifndef DISPLAYMANAGER_H
#define DISPLAYMANAGER_H

#include "GLFW/glfw3.h"

class DisplayManager {
public:
  static DisplayManager *getInstance();
  bool createDisplay();
  void updateDisplay();
  void closeDisplay();

  inline GLFWwindow *getDisplay() const { return this->display; }
  inline double getFrameTimeSeconds() const { return this->deltaFrameTime; }

private:
  DisplayManager() {}

  double lastFrameTime;
  double deltaFrameTime;

  GLFWwindow *display;
  static DisplayManager *instance;

  void centerWindow(GLFWwindow *window, GLFWmonitor *monitor);

  // Callbacks
  static void keyPressed(GLFWwindow *window, int key, int scancode, int action,
                         int mods);
};

#endif // !DISPLAYMANAGER_H
