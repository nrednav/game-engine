cmake_minimum_required(VERSION 3.20...3.26)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
  cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

project(
  game-engine
  VERSION 1.0
  DESCRIPTION "A C++ port of the OpenGL tutorials by ThinMatrix")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(glm REQUIRED)
find_package(OpenGL REQUIRED)

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

file(GLOB_RECURSE SOURCES "src/*.cpp" "src/*.h")

add_executable(game-engine src/Main.cpp src/Constants.h ${SOURCES})
target_include_directories(game-engine PUBLIC ${PROJECT_SOURCE_DIR}/include src)
target_link_libraries(game-engine glfw GLEW::glew glm OpenGL::GL)
