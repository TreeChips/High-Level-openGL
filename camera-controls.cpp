#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <cmath>
#include "highLevelOpenGL.h"

using namespace glm;

mat4 utilMoveCamera(vec3 pos, vec3 viewPoint, vec3 upDirection);    //Overload

mat4 utilMoveCamera(vec3 pos, float anglex, float angley, float distance, float anglez, vec3 upDirection) {
    vec3 point = vec3(distance*cos(anglex)*cos(angley), distance*cos(anglex)*sin(angley), distance*sin(anglex));
    mat4 view = lookAt(pos, point, upDirection);
    return view;
}

mat4 utilMoveCamera( vec3 pos, vec3 viewPoint, vec3 upDirection) {
    mat4 view = lookAt(pos, viewPoint, upDirection);
    return view;

}
