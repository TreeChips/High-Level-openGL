#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <utility>
#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include "include/stb_image.h"

GLuint glUtilCreateProgram(GLuint vertexShader, GLuint fragmentShader);

std::string READ_FILE(const char* filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Failed to open " << filePath << std::endl;
        return "";
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

GLuint glUtilCreateShader(GLenum type, const char* src) {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);
    return shader;
};

GLuint glUtilCreateProgram(const char* vertexShaderSourcePath, const char* fragmentShaderSourcePath) {
    std::string vertexShaderCode        = READ_FILE(vertexShaderSourcePath);
    std::string fragmentShaderCode     = READ_FILE(fragmentShaderSourcePath);

    const char* vertexShaderSource      = vertexShaderCode.c_str();
    const char* fragmentShaderSource   = fragmentShaderCode.c_str();

    const unsigned int vertexShader = glUtilCreateShader(GL_VERTEX_SHADER, vertexShaderSource);
    const unsigned int fragmentShader = glUtilCreateShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

    GLuint program = glUtilCreateProgram(vertexShader, fragmentShader);
    return program;

};

GLuint glUtilCreateProgram(uint vertexShader, uint fragmentShader) {
    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);
    return program;
}

std::pair<GLuint, GLuint> glUtilVABO(const float* vert, size_t count) {
    GLuint VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, count * sizeof(float), vert, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    return {VAO, VBO};
}

GLuint glLoadTexture(const char* path) {
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);  
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);  
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);  
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);

    if (data) {
        GLenum format = (nrChannels == 4) ? GL_RGBA : GL_RGB;
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cerr << "Failed to load texture: " << path << std::endl;
    }

    stbi_image_free(data);
    return textureID;
}

void glUtilUniformMatrix(GLuint program, const GLchar* uniformVar, int numberOfMatrices, glm::mat4 &pointer, bool transpose) {
    glUniformMatrix4fv(
        glGetUniformLocation(program, uniformVar),
        numberOfMatrices,
        transpose ? GL_TRUE : GL_FALSE,
        glm::value_ptr(pointer)
    );
}

void glUtilUniformMatrixMVP(GLuint program, glm::mat4 model, glm::mat4 view, glm::mat4 projection) {
    glUniformMatrix4fv(glGetUniformLocation(program, "model"), 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(glGetUniformLocation(program, "view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
}

void drawTriangles(GLuint vao, int offset, int vertices) {
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, offset, vertices);
}

void glmView(glm::mat4 *view, glm::vec3 target, glm::vec3 upDir, glm::vec3 pos) {
    *view = glm::lookAt(
        glm::vec3(pos),
        glm::vec3(target),
        glm::vec3(upDir)
    );
};

void glmPerspective(glm::mat4 *projection, int scr_width, int scr_height, float fov, float nearClippingPlane, float farClippingPlane) {
    *projection = glm::perspective(
        glm::radians(fov),
        (float)scr_width / scr_height,
        nearClippingPlane,
        farClippingPlane
    );
}

void glmRotate(glm::mat4 *model, float time, float angleX, float angleY, float angleZ, float scale) {
    *model = glm::rotate(
        glm::mat4(scale),
        time,
        glm::vec3(angleX, angleY, angleZ)
    );
};

GLFWwindow* glfwUtilCreateWindow(int versionMajor, int versionMinor, int profile, int scr_width, int scr_height, const char* title, GLFWmonitor* fullScreen, GLFWwindow* share) {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, versionMajor);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, versionMinor);
    glfwWindowHint(GLFW_OPENGL_PROFILE, profile);
    GLFWwindow* window = glfwCreateWindow(scr_width, scr_height, title, fullScreen, share);
    return window;
}
