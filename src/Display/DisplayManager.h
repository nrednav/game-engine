#ifndef DISPLAYMANAGER_H
#define DISPLAYMANAGER_H

#include "GLFW/glfw3.h"

class DisplayManager {
public:
  static DisplayManager* get_instance();
  bool create_display();
  void update_display();
  void close_display();

  inline GLFWwindow* get_display() const { return this->display; }
  inline double get_frame_time_seconds() const {
    return this->delta_frame_time;
  }

private:
  DisplayManager() {}

  double last_frame_time;
  double delta_frame_time;

  GLFWwindow* display;
  static DisplayManager* instance;

  void center_window(GLFWwindow* window, GLFWmonitor* monitor);

  // Callbacks
  static void key_pressed(GLFWwindow* window, int key, int scancode, int action,
                          int mods);
};

#endif // !DISPLAYMANAGER_H
