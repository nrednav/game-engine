#include "GL/glew.h"
#include "Display.h"
#include "Constants.h"

#include <GLFW/glfw3.h>
#include <iostream>
#include <stdexcept>

Display::Display() {
  if (!glfwInit()) {
    throw std::runtime_error{"Display/constructor: Failed to initialize GLFW"};
  }

  std::cout << "GLFW initialized." << std::endl;

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  this->window =
    glfwCreateWindow(DISPLAY_WIDTH, DISPLAY_HEIGHT, "Game Engine", NULL, NULL);

  if (!this->window) {
    glfwTerminate();

    throw std::runtime_error{
      "Display/constructor: Failed to create window with GLFW"
    };
  }

  std::cout << "Window created." << std::endl;

  glfwMakeContextCurrent(this->window);
  this->center_window(this->window, glfwGetPrimaryMonitor());
  glfwSetKeyCallback(this->window, key_pressed);

  glViewport(0, 0, DISPLAY_WIDTH, DISPLAY_HEIGHT);
  glfwSwapInterval(1);
  glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
  this->last_frame_time = glfwGetTime();

  if (glewInit() != GLEW_OK) {
    throw std::runtime_error{"Display/constructor: Failed to initialize GLEW"};
  }

  std::cout << "GLEW initialized." << std::endl;
}

Display::~Display() {
  glfwTerminate();
}

void Display::update() {
  glfwSwapBuffers(this->window);
  glfwPollEvents();

  double current_frame_time = glfwGetTime();

  this->delta_frame_time = current_frame_time - this->last_frame_time;
  this->last_frame_time = current_frame_time;
}

void Display::center_window(GLFWwindow* window, GLFWmonitor* monitor) {
  if (!monitor) {
    return;
  }

  const GLFWvidmode* mode = glfwGetVideoMode(monitor);

  if (!mode) {
    return;
  }

  int monitor_x;
  int monitor_y;

  glfwGetMonitorPos(monitor, &monitor_x, &monitor_y);

  int window_width;
  int window_height;

  glfwGetWindowSize(window, &window_width, &window_height);

  glfwSetWindowPos(
    window,
    monitor_x + (mode->width - window_width) / 2,
    monitor_y + (mode->height - window_height) / 2
  );
}

void Display::key_pressed(
  GLFWwindow* window,
  int key,
  int scancode,
  int action,
  int mods
) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, GL_TRUE);
  }
}
