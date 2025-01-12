#pragma once
#define GLFW_INCLUDE_NONE

#include "linmath.h"
#include "stb_image/stb_image.h"

#include <GLFW/glfw3.h>
#include <fstream>
#include <glad/glad.h>
#include <glm/glm/glm.hpp>
#include <iostream>
#include <random>
#include <sstream>
#include <string>

#define GLCall(x)   \
    GLClearError(); \
    x;              \
    assert(GLLogCall(#x, __FILE__, __LINE__))

inline void GLClearError();
inline bool GLLogCall(const char* function, const char* file, int line);

inline void GLClearError()
{
    while (glGetError() != GL_NO_ERROR)
        ;
}

inline bool GLLogCall(const char* function, const char* file, int line)
{
    while (GLenum error = glGetError()) {
        std::cout << "[OpenGL Error] (" << error << ") " << function << " " << file
                  << " " << line << std::endl;
        return false;
    }
    return true;
}
