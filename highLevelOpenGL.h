#ifndef GLUTILS_H
#define GLUTILS_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <utility> // for std::pair
#include <GLFW/glfw3.h>

GLuint glUtilCreateShader(GLenum type, const char* path);
GLuint glUtilCreateProgram(const char* vertexShaderPath, const char* fragmentShaderPath);
std::pair<GLuint, GLuint> glUtilVABO(const float* vertices, size_t count);
void glUtilUniformMatrixMVP(GLuint program, glm::mat4 model, glm::mat4 view, glm::mat4 projection);
void drawTriangles(GLuint vao, int start, int count);
void glmView(glm::mat4* view, glm::vec3 target = glm::vec3(0, 0, 0), glm::vec3 upDir = glm::vec3(0, 1, 0), glm::vec3 pos = glm::vec3(2, 2, 2));
void glmPerspective(glm::mat4* projection, int width, int height, float fov = 45.0f, float nearClippingPlane = 0.1f, float farClippingPlane = 100.0f);
void glmRotate(glm::mat4* model, float time, float x, float y, float z, float scale = 1.0f);
GLFWwindow* glfwUtilCreateWindow(int versionMajor, int versionMinor, int profile, int scr_width, int scr_height, const char* title, GLFWmonitor* fullScreen = NULL, GLFWwindow* share = NULL);
void moveCamera(vec3 pos, float anglex, float angley, float distance, float anglez, vec3 upDirection);
void moveCamera(vec3 pos, vec3 viewPoint, vec3 upDirection);
#endif
