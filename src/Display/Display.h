#ifndef DISPLAY_H
#define DISPLAY_H

#include "GLFW/glfw3.h"

class Display {
public:
  Display();
  ~Display();

  void update();

  inline GLFWwindow* get_window() const { return this->window; }
  inline double get_frame_time_seconds() const {
    return this->delta_frame_time;
  }

private:
  GLFWwindow* window;

  double last_frame_time;
  double delta_frame_time;

  void center_window(GLFWwindow* window, GLFWmonitor* monitor);

  // Callbacks
  static void
  key_pressed(GLFWwindow* window, int key, int scancode, int action, int mods);
};

#endif // !DISPLAY_H
