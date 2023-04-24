#include "GL/glew.h"
#include "DisplayManager.h"
#include "Constants.h"

#include <iostream>

DisplayManager* DisplayManager::instance = nullptr;

DisplayManager* DisplayManager::getInstance() {
  return instance = (instance != nullptr) ? instance : new DisplayManager();
}

bool DisplayManager::createDisplay() {
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
  this->centerWindow(display, glfwGetPrimaryMonitor());
  glfwSetKeyCallback(this->display, keyPressed);

  glViewport(0, 0, DISPLAY_WIDTH, DISPLAY_HEIGHT);
  glfwSwapInterval(1);
  glfwSetInputMode(this->display, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
  this->lastFrameTime = glfwGetTime();

  // Load GLEW
  if (glewInit() != GLEW_OK) {
    std::cout << "Failed to initialze GLEW..." << std::endl;
    return false;
  }
  std::cout << "GLEW initialized successfully..." << std::endl;

  return true;
}

void DisplayManager::updateDisplay() {
  glfwSwapBuffers(display);
  glfwPollEvents();

  double currentFrameTime = glfwGetTime();
  this->deltaFrameTime = currentFrameTime - this->lastFrameTime;
  this->lastFrameTime = currentFrameTime;
}

void DisplayManager::closeDisplay() { glfwTerminate(); }

void DisplayManager::centerWindow(GLFWwindow* window, GLFWmonitor* monitor) {
  if (!monitor)
    return;

  const GLFWvidmode* mode = glfwGetVideoMode(monitor);
  if (!mode)
    return;

  int monitorX, monitorY;
  glfwGetMonitorPos(monitor, &monitorX, &monitorY);

  int windowWidth, windowHeight;
  glfwGetWindowSize(window, &windowWidth, &windowHeight);

  glfwSetWindowPos(window, monitorX + (mode->width - windowWidth) / 2,
                   monitorY + (mode->height - windowHeight) / 2);
}

// Callbacks
void DisplayManager::keyPressed(GLFWwindow* window, int key, int scancode,
                                int action, int mods) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GL_TRUE);
}
