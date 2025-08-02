#include <GLFW/glfw3.h>
#include "highLevelOpenGL.h"

GLFWwindow* glfwUtilCreateWindow(int versionMajor, int versionMinor, int profile, int scr_width, int scr_height, const char* title, GLFWmonitor* fullScreen, GLFWwindow* share) {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, versionMajor);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, versionMinor);
    glfwWindowHint(GLFW_OPENGL_PROFILE, profile);
    GLFWwindow* window = glfwCreateWindow(scr_width, scr_height, title, fullScreen, share);
    return window;
}
