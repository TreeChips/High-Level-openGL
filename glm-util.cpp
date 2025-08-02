#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "highLevelOpenGL.h"

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