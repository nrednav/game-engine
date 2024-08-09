#include "GL/glew.h"
#include "DisplayManager.h"
#include "Constants.h"

#include <iostream>

DisplayManager* DisplayManager::instance = nullptr;

DisplayManager* DisplayManager::get_instance() {
  return instance = (instance != nullptr) ? instance : new DisplayManager();
}

bool DisplayManager::create_display() {
  // Initialize GLFW
  if (!glfwInit()) {
    std::cout << "Failed to initialize GLFW..." << std::endl;
    return false;
  }

  std::cout << "GLFW initialized successfully..." << std::endl;

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  this->display =
    glfwCreateWindow(DISPLAY_WIDTH, DISPLAY_HEIGHT, "ThinMatrix", NULL, NULL);

  if (!this->display) {
    glfwTerminate();
    return false;
  }

  std::cout << "Created display..." << std::endl;

  glfwMakeContextCurrent(this->display);
  this->center_window(display, glfwGetPrimaryMonitor());
  glfwSetKeyCallback(this->display, key_pressed);

  glViewport(0, 0, DISPLAY_WIDTH, DISPLAY_HEIGHT);
  glfwSwapInterval(1);
  glfwSetInputMode(this->display, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
  this->last_frame_time = glfwGetTime();

  // Load GLEW
  if (glewInit() != GLEW_OK) {
    std::cout << "Failed to initialze GLEW..." << std::endl;
    return false;
  }
  std::cout << "GLEW initialized successfully..." << std::endl;

  return true;
}

void DisplayManager::update_display() {
  glfwSwapBuffers(display);
  glfwPollEvents();

  double current_frame_time = glfwGetTime();

  this->delta_frame_time = current_frame_time - this->last_frame_time;
  this->last_frame_time = current_frame_time;
}

void DisplayManager::close_display() {
  glfwTerminate();
}

void DisplayManager::center_window(GLFWwindow* window, GLFWmonitor* monitor) {
  if (!monitor)
    return;

  const GLFWvidmode* mode = glfwGetVideoMode(monitor);
  if (!mode)
    return;

  int monitor_x, monitor_y;
  glfwGetMonitorPos(monitor, &monitor_x, &monitor_y);

  int window_width, window_height;
  glfwGetWindowSize(window, &window_width, &window_height);

  glfwSetWindowPos(
    window,
    monitor_x + (mode->width - window_width) / 2,
    monitor_y + (mode->height - window_height) / 2
  );
}

// Callbacks
void DisplayManager::key_pressed(
  GLFWwindow* window,
  int key,
  int scancode,
  int action,
  int mods
) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GL_TRUE);
}
