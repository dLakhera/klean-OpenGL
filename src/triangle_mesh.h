#pragma once

#include "config.h"
#include <chrono>
#include <random>

class TriangleMesh {
private:
    std::vector<GLuint> vbo;
    GLuint ebo = 0;
    GLuint vao = 0;
    unsigned int vertex_count;

    // std::mt19937 rgn;

public:
    TriangleMesh();
    void draw();
    void updateData();
    ~TriangleMesh();
};
